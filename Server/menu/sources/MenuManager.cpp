#include	<algorithm>
#include	<iostream>
#include	"Game.h" /*Must be included in first*/
#include	"Database.hh"
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
#include	"ThreadEvent.hpp"

namespace	menu
{
  Manager::Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue<ARequest *> &output) :
    _input(input), _output(output)
  {
    _server.monitor(true, false);
    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;
    _requestCallback[requestCode::auth::NEW_USER] = &newUser;

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
    ARequest *req = client->menu().requestPop();

    while (req != 0)
      {
	request_callback_map::iterator	it = _requestCallback.find(req->code());

	if (it != _requestCallback.end())
	  it->second(req, client, this);
	req = client->menu().requestPop();
      }
  }

  void	Manager::updateClients()
  {
    std::vector< ::Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end();)
      {
	(*it)->menu().update();
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

  bool		Manager::isConnected(const std::string &clientName)
  {
    return (std::find_if(_clients.begin(), _clients.end(), Predicate(clientName)) != _clients.end());
  }

  ///////////////////////
  // Request Modifiers //
  ///////////////////////

  ////////////////////
  // Try to connect //
  ////////////////////
  void	Manager::tryConnect(ARequest *req, ::Client *client, Manager *manager)
  {
    Auth::Connect	*request = dynamic_cast<Auth::Connect *>(req);

#if defined(DEBUG)
    std::cout << request->username() << ":" << request->password() << std::endl;
#endif
    if (!client->menu().authenticated() && !manager->isConnected(request->username()))
      {
	if (!Database::getInstance().clientExist(request->username(), request->password()))
	  {
#if defined(DEBUG)
	    std::cout << client << ": Authentication succeed" << std::endl;
#endif
	    client->menu().username(request->username());
	    client->menu().password(request->password());
	    client->menu().authenticated(true);

	    requestCode::SessionID id = SessionRequest::Unique();
	    client->menu().sessionID(id);
	    client->id(id);

	    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
	    client->menu().requestPush(new SessionRequest(client->id()));
	    delete req;
	    return ;
	  }
      }
#if defined(DEBUG)
    std::cout << client << ": Authentication failed" << std::endl;
#endif
    client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
    delete req;
  }

  ///////////////////////
  // Create a new User //
  ///////////////////////
  void	Manager::newUser(ARequest *req, ::Client *client, Manager *manager)
  {
    Auth::NewUser	*request = dynamic_cast<Auth::NewUser *>(req);

    (void)manager;
    if (!client->menu().authenticated())
      {
	if (Database::getInstance().newClient(request->username(), request->password()))
	  {
	    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
	    delete req;
	    return ;
	  }
      }
#if defined(DEBUG)
    std::cout << client << ": Can't create new user named" << request->username() << std::endl;
#endif
    client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
    delete req;
  }

  ////////////////////
  // Launch a party //
  ////////////////////
  void	Manager::launchGame(ARequest *req, ::Client *client, Manager *manager)
  {
    std::list<game::Client *>	players;
    Game			*new_game = new Game(players);
    game::Client	*new_client = new game::Client();
    game::Player	*player = new game::Player(42, new_game->UniqueId());

    new_client->player(player);
    players.push_back(new_client);
    client->game().game(new_game);
    client->game().player(player);
    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
    client->menu().requestPush(new Party::Launch(Party::Launch::Unique()));
    manager->sendGame(new_game);
    delete req;
  }

  ///////////////
  // Predicate //
  ///////////////

  Manager::Predicate::Predicate(const std::string &login) :
    _login(login)
  {

  }

  bool	Manager::Predicate::operator()(const ::Client *client)
  {
    return (client->menu().username() == _login);
  }
}
