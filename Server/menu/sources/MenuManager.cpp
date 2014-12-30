#include	<algorithm>
#include	<iostream>
#include	"Database.hh"
#include	"MenuClient.hh"
#include	"MenuManager.hh"
#include	"MenuException.hh"
//#include	"sys.hh"
#include	"Client.hh"
#include	"NetException.h"
#include	"AuthRequest.hh"
#include	"SessionRequest.hh"
#include	"PartyRequest.hh"
#include	"ServerRequest.hh"
#include	"MenuGame.hh"
#include	"Callback.hh"
#include	"Application.hh"
#include	"RequestCode.hh"
#include	"ChatRecvRequest.h"
#include	"ChatSendRequest.h"

namespace	menu
{
  Manager::Manager(Manager::input_event &input, Manager::output_event &output) :
    _th(Func::Bind(&Manager::routine, this)), _active(true),
    _input(input), _output(output)
  {
    _server.monitor(true, false);

    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;
    _requestCallback[requestCode::auth::NEW_USER] = &newUser;
    _requestCallback[requestCode::party::LIST] = &listGames;
    _requestCallback[requestCode::party::CREAT] = &createGame;
    _requestCallback[requestCode::party::JOIN] = &joinGame;
    _requestCallback[requestCode::party::CANCEL] = &cancelGame;
    _requestCallback[requestCode::party::CLI_START] = &launchGame;
    _requestCallback[requestCode::chat::SEND_MSG] = &chatRecv;
    _requestCallback[requestCode::root::SHUTDOWN] = &shutdown;
  }

  Manager::~Manager()
  {
    _active = false;
    join();
    for (game_list::iterator it = _games.begin(); it != _games.end(); ++it)
      delete *it;
    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
      delete *it;
  }

  void	Manager::join()
  {
    _th.join();
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
      Application::log << e.what() << std::endl;
      throw menu::Exception("Unable to init Menu Manager");
    }
  }

  void	Manager::run()
  {
    _th.run();
#if defined(DEBUG)
    Application::log << "Menu manager started..." << std::endl;
#endif
  }

  void	Manager::checkNewClient()
  {
    if (_server.read())
    {
      Client		*menuClient = new Client(_server.accept());

      _clients.push_back(menuClient);
      _monitor.setMonitor(*(menuClient->TcpLayer()));
      _output.push(new ApplicationCallback<requestCode::SessionID>(menuClient->sessionID(), &Application::newClient));
    }
  }

  void	Manager::clientRequest(Client *client)
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

  void	Manager::delPlayerParty(Game *game, Client *client)
  {
#if defined(DEBUG)
    Application::log << "menu::Manager::delPlayerParty() - "
		     << game << ", Game Name: " << game->partyName()
		     << " - Client Name: " << client->username() << std::endl;
#endif
    game->delPlayer(client->username());
    client->requestPush(new Party::Stopped());
    broadcast(Party::Update(game->partyName(),
			    game->availableSlots(),
			    game->maxPlayers(),
			    game->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
			    requestCode::party::UPDATE_GAME));
  }

  void	Manager::delParty(Game *game)
  {
#if defined(DEBUG)
    Application::log << "menu::Manager::delParty() - "
		     << game << ", Game Name: " << game->partyName() << std::endl;
#endif
    game->broadcast(Party::Stopped());
    broadcast(Party::Update(game->partyName(),
			    game->availableSlots(),
			    game->maxPlayers(),
			    game->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
			    requestCode::party::CANCELED));
    delete game;
  }

  void	Manager::disconnectClient(Client *client)
  {
#if defined(DEBUG)
    Application::log << "menu::Manager::disconnectClients() Client disconnected("
		     << client << ")" << std::endl;
#endif
    if (client->currentGame() != 0)
    {
      game_list::iterator	it = find_if(_games.begin(), _games.end(),
					     PredicateParty(client->currentGame()->partyName()));

      if (it != _games.end())
      {
#if defined(DEBUG)
	Application::log << "menu::Manager::disconnectClients()"
			 << "Client was in a game: " << client->currentGame()->partyName() << std::endl;
#endif
	if ((*it)->owner() == client)
	{
	  delParty(*it);
	  _games.erase(it);
	}
	else
	  delPlayerParty(*it, client);
      }
    }
    _monitor.unsetMonitor(*client->TcpLayer());
    // client->inUse(false);
  }

  void	Manager::updateClients()
  {
    client_list::iterator it;

    for (it = _clients.begin(); it != _clients.end();)
    {
      (*it)->update();
      if ((*it)->isTCPDisconnected())
      {
	Client	*processed = *it;
	disconnectClient(processed);
	it = _clients.erase(it);
	_output.push(new ApplicationCallback<requestCode::SessionID>(processed->sessionID(), &Application::clientDisconnected));
	delete processed;
	continue;
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
      (*it)->requestPush(new Req(req));
  }

  void                  Manager::updateCallback()
  {
    ICallbacks          *cb;

    while ((cb = _input.pop(false)) != 0)
    {
      (*cb)();
      delete cb;
    }
  }

  void	Manager::stop()
  {
    _active = false;
  }

  void	Manager::routine(Manager *self)
  {
    while (self->_active)
    {
      try
      {
	struct timeval	def;
	def.tv_sec = 1;
	def.tv_usec = 0;
	self->_monitor.setOption(net::streamManager::TIMEOUT, def);
	self->_monitor.run();
	self->updateCallback();
	self->updateClients();
      }
      catch (net::Exception &e)
      {
	self->_active = false;
	Application::log << "Fatal error : " << e.what() << " in menu::Manager::routine" << std::endl;
      }
      self->checkNewClient();
    }
  }

  bool		Manager::isConnected(const std::string &clientName)
  {
    return (std::find_if(_clients.begin(), _clients.end(),
			 PredicateClient(clientName)) != _clients.end());
  }


  ////////////////////////
  // Callback Functions //
  ////////////////////////

  void		Manager::clientLeaveGame(requestCode::SessionID clientID)
  {
    client_list::iterator	itCli = std::find_if(_clients.begin(), _clients.end(),
						     PredicateClient(clientID));
    game_list::iterator	itGame = std::find_if(_games.begin(), _games.end(),
					      PredicateParty((*itCli)->currentGame()->partyName()));

    (*itCli)->currentGame(0);
    (*itGame)->delPlayer((*itCli)->username());
  }

  void		Manager::endGame(Game *game)
  {
    game_list::iterator	it;

    it = std::find_if(_games.begin(), _games.end(), PredicateParty(game->partyName()));
    if (it == _games.end())
      return;
    for (client_list::iterator itCli = (*it)->getClients().begin();
	 itCli != (*it)->getClients().end(); ++itCli)
      (*itCli)->currentGame(0);

    broadcast(Party::Update(game->partyName(),
			    game->availableSlots(),
			    game->maxPlayers(),
			    game->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
			    requestCode::party::FINISHED));
    _games.erase(it);
  }

  ///////////////////////
  // Request Modifiers //
  ///////////////////////

  ////////////////////
  // Try to connect //
  ////////////////////
  void	Manager::tryConnect(ARequest *req, Client *client, Manager *manager)
  {
    Auth::Connect	*request = dynamic_cast<Auth::Connect *>(req);

#if defined(DEBUG)
    Application::log << client << ":" << request->username() << ":" << request->password() << ", "
		     << std::boolalpha << "already connected ? "
		     << !manager->isConnected(request->username()) << ", "
		     << std::boolalpha << "already authenticated ? "
		     << client->authenticated() << std::endl;
#endif
    if (!client->authenticated() && !manager->isConnected(request->username()))
    {
      Database::Client	c;

      if (Database::getInstance().clientExist(request->username(), request->password()) &&
	  Database::getInstance().getClient(request->username(), c))
      {
#if defined(DEBUG)
	Application::log << client << ": Authentification succeed" << std::endl;
#endif
	client->username(c.login);
	client->password(c.password);
	client->permissions(c.rights);
	client->authenticated(true);

	if (c.session == 0)
	  c.session = SessionRequest::Unique();
	client->sessionID(c.session);

	client->requestPush(new ServerRequest(requestCode::server::OK));
	client->requestPush(new SessionRequest(client->sessionID()));
	listGames(0, client, manager);
	delete req;
	return ;
      }
    }
#if defined(DEBUG)
    Application::log << client << ": Authentification failed" << std::endl;
#endif
    client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
    delete req;
  }

  ///////////////////////
  // Create a new User //
  ///////////////////////
  void	Manager::newUser(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::newUser" << std::endl;
#endif
    Auth::NewUser	*request = dynamic_cast<Auth::NewUser *>(req);

    (void)manager;
    if (client->authenticated() && client->permissions() == database::SUPER_USER)
    {
      if (Database::getInstance().newClient(request->username(), request->password()))
      {
	client->requestPush(new ServerRequest(requestCode::server::OK));
	delete req;
	return ;
      }
    }
#if defined(DEBUG)
    Application::log << client << ": Can't create new user named" << request->username() << std::endl;
#endif
    client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
    delete req;
  }

  ////////////////
  // List games //
  ////////////////
  void	Manager::listGames(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::listGames" << std::endl;
#endif
    if (!client->authenticated())
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return ;
    }
    for (game_list::iterator it = manager->_games.begin(); it != manager->_games.end() ; ++it)
    {
#if defined(DEBUG)
      Application::log << "Manager::listGames(): " << *it << ", GameName: "
		       << (*it)->partyName() << std::endl;
#endif
      client->requestPush(new Party::Update((*it)->partyName(),
					    (*it)->availableSlots(),
					    (*it)->maxPlayers(),
					    (*it)->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
					    (*it)->status()));
    }
    delete req;
  }

  /////////////////
  // create game //
  /////////////////
  void	Manager::createGame(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::createGame" << std::endl;
#endif
    Party::Create	*request = dynamic_cast<Party::Create *>(req);

    if (!client->authenticated() || client->inLobby() ||
	find_if(manager->_games.begin(), manager->_games.end(), PredicateParty(request->_partyName)) != manager->_games.end())
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return ;
    }
    menu::Game	*game = new menu::Game(client);

    game->partyName(request->_partyName);
    game->maxPlayers(request->_maxPlayers);
    if (request->_isPassword == requestCode::party::PASS)
      game->password(request->_partyPass);
    manager->_games.push_back(game);
    delete req;
    game->status(requestCode::party::OUT_GAME);
    client->requestPush(new ServerRequest(requestCode::server::OK));
    manager->broadcast(Party::Update(game->partyName(),
				     game->availableSlots(),
				     game->maxPlayers(),
				     game->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
				     game->status()));
  }

  ///////////////
  // join game //
  ///////////////
  void	Manager::joinGame(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::JoinGame" << std::endl;
#endif
    Party::Join	*request = dynamic_cast<Party::Join *>(req);
    game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
				     PredicateParty(request->_partyName));

    if (!client->authenticated() || it == manager->_games.end() ||
	!(*it)->newPlayer(client))
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return ;
    }
    client->requestPush(new ServerRequest(requestCode::server::OK));
    manager->broadcast(Party::Update((*it)->partyName(),
				     (*it)->availableSlots(),
				     (*it)->maxPlayers(),
				     (*it)->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
				     (*it)->status()));
    delete req;
  }

  /////////////////
  // cancel game //
  /////////////////
  void	Manager::cancelGame(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::cancelGame" << std::endl;
#endif

    if (client->authenticated() || client->currentGame() != 0)
    {
      game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
					     PredicateParty(client->currentGame()->partyName()));

      if (it != manager->_games.end() && (*it)->status() == requestCode::party::OUT_GAME)
      {
#if defined(DEBUG)
	Application::log << "menu::Manager::cancelGame(): " << std::endl;
#endif
	if ((*it)->owner() == client)
	{
	  manager->delParty(*it);
	  manager->_games.erase(it);
	  delete req;
	  return ;
	}
	else
	{
	  manager->delPlayerParty(*it, client);
	  delete req;
	  return ;
	}
      }

    }

    client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
    delete req;
    return ;
  }

  ////////////////////
  // Launch a party //
  ////////////////////
  void	Manager::launchGame(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::launchGame" << std::endl;
#endif
    game_list::iterator	it = find_if(manager->_games.begin(), manager->_games.end(),
				     PredicateOwner(client));

    if (!client->authenticated() || it == manager->_games.end() ||
	(*it)->status() != requestCode::party::OUT_GAME)
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return;
    }
    client->requestPush(new ServerRequest(requestCode::server::OK));
    (*it)->broadcast(Party::Launch(Party::Launch::Unique()));
    (*it)->status(requestCode::party::IN_GAME);
    manager->broadcast(Party::Update((*it)->partyName(),
				     (*it)->availableSlots(),
				     (*it)->maxPlayers(),
				     (*it)->ispassword() ? requestCode::party::PASS : requestCode::party::NO_PASS,
				     (*it)->status()));
    manager->_output.push(new ApplicationCallback<menu::Game *>(*it, &Application::newGame));
    delete req;
  }

  //////////////
  // Shutdown //
  //////////////
  void	Manager::shutdown(ARequest *req, Client *client, Manager *manager)
  {
    if (!client->authenticated() || client->permissions() != database::SUPER_USER)
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return;
    }
    client->requestPush(new ServerRequest(requestCode::server::OK));
    delete req;
    manager->_output.push(new ApplicationCallback<Client *>(client, &Application::stop));
  }

  //////////////
  //   Chat   //
  //////////////
  void	Manager::chatRecv(ARequest *req, Client *client, Manager *manager)
  {
#if defined(DEBUG)
    Application::log << "Manager::chatRecv" << std::endl;
#endif

    if (!client->authenticated())
    {
      client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      delete req;
      return;
    }
    manager->broadcast(ChatRecvRequest(dynamic_cast<ChatSendRequest *>(req)->msg()));
    delete req;
  }

  ///////////////
  // Predicate //
  ///////////////

  Manager::PredicateClient::PredicateClient(const std::string &login) :
    _login(login), _id(0) // ID can't be 0
  {

  }

  Manager::PredicateClient::PredicateClient(const requestCode::SessionID id) :
    _id(id)
  {

  }

  bool	Manager::PredicateClient::operator()(const Client *client)
  {
    return (client->username() == _login || client->sessionID() == _id);
  }

  Manager::PredicateParty::PredicateParty(const std::string &partyName) :
    _partyName(partyName)
  {

  }

  bool	Manager::PredicateParty::operator()(const menu::Game *game)
  {
    return (game->partyName() == _partyName);
  }

  Manager::PredicateOwner::PredicateOwner(const Client *client) :
    _client(client)
  {

  }

  bool	Manager::PredicateOwner::operator()(const menu::Game *game)
  {
    return (game->owner() == _client);
  }
}
