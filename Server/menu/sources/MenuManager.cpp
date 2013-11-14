#include	<iostream>
#include	"Game.h" /*Must be included in first*/
#include	"MenuManager.hh"
#include	"MenuException.hh"
#include	"sys.hh"
#include	"Client.hh"
#include	"NetException.h"
#include	"AuthRequest.hh"
#include	"SessionRequest.hh"
#include	"PartyRequest.hh"
#include	"ServerRequest.hh"
#include	"GameClient.hh"
#include	"Player.h"
#include	"Game.h"
#include	"ThreadEvent.hpp"

namespace	menu
{
	Manager::Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue<ARequest *> &output) :
		_input(input), _output(output)
  {
    _server.monitor(true, false);
    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;

    _requestCallback[requestCode::party::CLI_START] = &launchGame;
  }

  Manager::~Manager()
  {

  }

  void	Manager::initialize(unsigned short int port)
  {
    try
      {
	_server.initialize(port);
	_monitor.setMonitor(_server);
      }
    catch (const net::Exception e)
      {
	std::cout << e.what() << std::endl;
	throw menu::Exception("Unable to init Menu Manager");
      }
  }

  void	Manager::run()
  {
    std::cout << "Menu manager started..." << std::endl;
    routine(this);
  }

  void	Manager::checkNewClient()
  {
    if (_server.read())
      {
	::Client	*client = new ::Client(_server.accept());

	_clients.push_back(client);
	_monitor.setMonitor(*(client->menu().TcpLayer()));
      }
  }

  void	Manager::clientRequest(::Client *client)
  {
    ARequest *req = client->requestPop();

    while (req != 0)
      {
	request_callback_map::iterator	it = _requestCallback.find(req->code());

	if (it != _requestCallback.end())
	  it->second(req, client, this);
	req = client->requestPop();
      }
  }

  void	Manager::updateClients()
  {
    std::vector< ::Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end();)
      {
	(*it)->update();
	if ((*it)->menu().isTCPDisconnected())
	  {
	    ::Client	*client = *it;
#if defined(DEBUG)
	    std::cerr << "Client disconnected(" << *it << ")" << std::endl;
#endif
	    _monitor.unsetMonitor(*client->menu().TcpLayer());
	    it = _clients.erase(it);
	    delete client;
	    continue ;
	  }
	clientRequest(*it);
	(*it)->finalize();
	++it;
      }
  }

  void	Manager::routine(Manager *thisPtr)
  {
    while (true)
      {
	thisPtr->_monitor.run();
	thisPtr->updateClients();
	thisPtr->checkNewClient();
	}
  }

  void		Manager::sendGame(Game *game)
  {
    (void)game;
  }

  ///////////////////////
  // Request Modifiers //
  ///////////////////////

  void	Manager::tryConnect(ARequest *req, ::Client *client, Manager *manager)
  {
    Auth::Connect	*request = dynamic_cast<Auth::Connect *>(req);

#if defined(DEBUG)
    std::cout << request->username() << ":" << request->password() << std::endl;
#endif
    (void)manager;
    if (!client->menu().authenticated())
      {
#if defined(DEBUG)
	std::cout << client << ": Authentication succeed" << std::endl;
#endif
	client->menu().username(request->username());
	client->menu().password(request->password());
	client->menu().authenticated(true);
	client->requestPush(new ServerRequest(requestCode::server::OK));
	client->requestPush(new SessionRequest(SessionRequest::Unique()));
      }
    else
      {
#if defined(DEBUG)
	std::cout << client << ": Authentication failed" << std::endl;
#endif
	client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      }
    delete req;
  }

  void	Manager::launchGame(ARequest *req, ::Client *client, Manager *manager)
  {
    game::Player		*player = new game::Player(42);
    std::list<game::Client *>	players;
    Game			*new_game;
	game::Client	*new_client = new game::Client();

	new_client->player(player);
    players.push_back(new_client);
    new_game = new Game(players);
    client->game().game(new_game);
    client->game().player(player);
    client->requestPush(new ServerRequest(requestCode::server::OK));
    client->requestPush(new Party::Launch(Party::Launch::Unique()));
    manager->sendGame(new_game);
    delete req;
  }
}
