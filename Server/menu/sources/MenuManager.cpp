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
#include	"MenuGame.hh"

namespace	menu
{
  Manager::Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue< ::Game *> &output) :
    _active(true), _input(input), _output(output)
  {
    _server.monitor(true, false);
    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;
    _requestCallback[requestCode::auth::NEW_USER] = &newUser;

    _requestCallback[requestCode::party::LIST] = &listGames;
    _requestCallback[requestCode::party::CREAT] = &createGame;
    _requestCallback[requestCode::party::JOIN] = &joinGame;
    _requestCallback[requestCode::party::CANCEL] = &cancelGame;
    _requestCallback[requestCode::party::CLI_START] = &launchGame;

    _requestCallback[requestCode::root::SHUTDOWN] = &shutdown;
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
    client_list::iterator it;

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

  template <typename Req>
  void	Manager::broadcast(const Req &req)
  {
    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
      {
	Req	*broadcasted = new Req(req);

	(*it)->menu().requestPush(broadcasted);
      }
  }

  void	Manager::routine(Manager *thisPtr)
  {
    while (thisPtr->_active)
      {
		try
		{
			thisPtr->_monitor.run();
			thisPtr->updateClients();
		}
		catch (net::Exception &e)
		{
			thisPtr->_active = false;
			std::cerr << "Fatal error : " << e.what() << " in menu::Manager::routine" << std::endl;
		}
		thisPtr->checkNewClient();
      }
  }

  void		Manager::sendGame(Game *game)
  {
    (void)game;
  }

  bool		Manager::isConnected(const std::string &clientName)
  {
    return (std::find_if(_clients.begin(), _clients.end(),
			 PredicateClient(clientName)) != _clients.end());
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
	Database::Client	c;

	if (!Database::getInstance().clientExist(request->username(), request->password()) ||
	    !Database::getInstance().getClient(request->username(), c))
	  {
#if defined(DEBUG)
	    std::cout << client << ": Authentication succeed" << std::endl;
#endif
	    client->menu().username(c.login);
	    client->menu().password(c.password);
	    client->menu().permissions(c.rights);
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
#if defined(DEBUG)
    std::cout << "Manager::newUser" << std::endl;
#endif
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

  ////////////////
  // List games //
  ////////////////
  void	Manager::listGames(ARequest *req, ::Client *client, Manager *manager)
  {
#if defined(DEBUG)
    std::cout << "Manager::listGames" << std::endl;
#endif
    if (!client->menu().authenticated())
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return ;
      }
    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
    for (game_list::iterator it = manager->_games.begin(); it != manager->_games.end() ; ++it)
      client->menu().requestPush(new Party::Update((*it)->partyName(),
						   (*it)->availableSlots(),
						   (*it)->maxPlayers(),
						   (*it)->ispassword(),
						   (*it)->status()));
    delete req;
  }

  /////////////////
  // create game //
  /////////////////
  void	Manager::createGame(ARequest *req, ::Client *client, Manager *manager)
  {
#if defined(DEBUG)
    std::cout << "Manager::createGame" << std::endl;
#endif
    Party::Create	*request = dynamic_cast<Party::Create *>(req);

    if (!client->menu().authenticated() || find_if(manager->_games.begin(), manager->_games.end(),
						   PredicateParty(request->_partyName)) == manager->_games.end())
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return ;
      }
    menu::Game	*game = new menu::Game(client);

    game->partyName(request->_partyName);
    game->maxPlayers(request->_maxPlayers);
    if (request->_isPassword == Party::Create::PASS)
      game->password(request->_partyPass);
    manager->_games.push_back(game);
    delete req;
    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
  }

  ///////////////
  // join game //
  ///////////////
  void	Manager::joinGame(ARequest *req, ::Client *client, Manager *manager)
  {
#if defined(DEBUG)
    std::cout << "Manager::JoinGame" << std::endl;
#endif
    Party::Join	*request = dynamic_cast<Party::Join *>(req);
    game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
				     PredicateParty(request->_partyName));

    if (!client->menu().authenticated() || it == manager->_games.end() || !(*it)->newPlayer(client))
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return ;
      }
    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
    manager->broadcast(Party::Update((*it)->partyName(),
				     (*it)->availableSlots(),
				     (*it)->maxPlayers(),
				     (*it)->ispassword(),
				     (*it)->status()));
    delete req;
  }

  /////////////////
  // cancel game //
  /////////////////
  void	Manager::cancelGame(ARequest *req, ::Client *client, Manager *manager)
  {
#if defined(DEBUG)
    std::cout << "Manager::cancelGame" << std::endl;
#endif
    game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
				     PredicateOwner(client));

    if (!client->menu().authenticated() || it == manager->_games.end() ||
	(*it)->status() != Game::OUT_GAME)
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return ;
      }
    client->menu().requestPush(new ServerRequest(requestCode::server::OK));
    manager->broadcast(Party::Update((*it)->partyName(),
				     (*it)->availableSlots(),
				     (*it)->maxPlayers(),
				     (*it)->ispassword(),
				     Game::CANCELED));
    manager->_games.erase(it);
    delete req;
  }

  ////////////////////
  // Launch a party //
  ////////////////////
  void	Manager::launchGame(ARequest *req, ::Client *client, Manager *manager)
  {
#if defined(DEBUG)
    std::cout << "Manager::launchGame" << std::endl;
#endif
    game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
				     PredicateOwner(client));

    if (!client->menu().authenticated() || it == manager->_games.end() ||
	(*it)->status() != Game::OUT_GAME)
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return;
      }
    manager->_output.push((*it)->initialize());
    //::Game	*new_game = new ::Game();

    //(*it)->game(new_game);

    // std::list<game::Client *>	players;
    // Game			*new_game = new Game(players);
    // game::Client	*new_client = new game::Client();
    // game::Player	*player = new game::Player(42, new_game->UniqueId());

    // new_client->player(player);
    // players.push_back(new_client);
    // client->game().game(new_game);
    // client->game().player(player);
    // client->menu().requestPush(new ServerRequest(requestCode::server::OK));
    // client->menu().requestPush(new Party::Launch(Party::Launch::Unique()));
    // manager->sendGame(new_game);
    delete req;
  }

  //////////////
  // Shutdown //
  //////////////
  void	Manager::shutdown(ARequest *req, ::Client *client, Manager *manager)
  {
    if (!client->menu().authenticated() || client->menu().permissions() != database::SUPER_USER)
      {
	client->menu().requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
	delete req;
	return;
      }
    manager->_active = false;
  }

  ///////////////
  // Predicate //
  ///////////////

  Manager::PredicateClient::PredicateClient(const std::string &login) :
    _login(login)
  {

  }

  bool	Manager::PredicateClient::operator()(const ::Client *client)
  {
    return (client->menu().username() == _login);
  }

  Manager::PredicateParty::PredicateParty(const std::string &partyName) :
    _partyName(partyName)
  {

  }

  bool	Manager::PredicateParty::operator()(const menu::Game *game)
  {
    return (game->partyName() == _partyName);
  }

  Manager::PredicateOwner::PredicateOwner(const ::Client *client) :
    _client(client)
  {

  }

  bool	Manager::PredicateOwner::operator()(const menu::Game *game)
  {
    return (game->owner() == _client);
  }
}
