#include	<iostream>
#include	<algorithm>
#include	"Game.hh"
#include	"ICallbacks.hh"
#include	"GameManager.hh"
#include	"Client.hh"
#include	"AGameRequest.hh"
#include	"sys.hh"
#include	"Bind.hpp"
#include	"NetException.h"
// #include	"ClientAccepted.h"
#include	"Protocol.hpp"
#include	"GameClient.hh"
#include	"GamePool.hh"
#include	"Callback.hh"
#include	"Application.hh"

namespace	game
{

  ////////////////////////////
  // Constructor/Destructor //
  ////////////////////////////

  Manager::Manager(Manager::input_event &input, Manager::output_event &output) :
    _th(Func::Bind(&Manager::routine, this)), _input(input), _output(output)
  {
    srand((unsigned int)(time(NULL)));
    _server.monitor(true, false);
  }

  Manager::~Manager()
  {
    _active = false;
    join();
    for (client_list::iterator it = _gameClients.begin(); it != _gameClients.end(); ++it)
      delete *it;
    // for (game_list::iterator it = _games.begin(); it != _games.end(); ++it)
    //   delete *it;
  }

  /////////////////////////////
  // Manager Start/Stop/Join //
  /////////////////////////////

  void	Manager::join()
  {
    _th.join();
  }

  void			Manager::stop()
  {
    _active = false;
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
      Application::log << e.what()  << std::endl;
      throw net::Exception("Unable to init Game Manager");
    }
  }

  void	Manager::run()
  {
    _active = true;
    _th.run();
#if defined(DEBUG)
    Application::log << "Game manager started..."  << std::endl;
#endif
  }


  /////////////////////////////
  // Recv Request Management //
  /////////////////////////////

  bool	Manager::getRequest(AGameRequest *&request)
  {
    int					extracted;
    std::vector<cBuffer::Byte>		buf;

    _server.lookRead(buf, 512);
#if defined(DEBUG)
    Application::log<< "Manager::getRequest::buf = " << buf.size()
		    << log::Log::hexDump(buf) << std::endl;
#endif
    try
    {
      request = dynamic_cast<AGameRequest *>(Protocol::consume(buf, extracted));
      if (request == 0)
	throw Protocol::ConstructRequest("Request is not a GameRequest");
    }
    catch (Protocol::ConstructRequest &e)
    {
#if defined(DEBUG)
      Application::log << "Failed to create request: " << e.what()  << std::endl;
#endif
      return (false);
    }
    _server.readFromBuffer(buf, extracted);
    return true;
  }

  void					Manager::dispatchMessages()
  {
    client_list::iterator		it;
    AGameRequest			*req;

    _server.recv();
    while (getRequest(req))
    {
      it = std::find_if(_gameClients.begin(), _gameClients.end(), predicate(req->SessionID()));
      if (it != _gameClients.end())
      {
#if defined(DEBUG)
	Application::log << "Client " << (*it)->sessionID()
			 << "send a request of type " << req->code() << std::endl;
#endif
	(*it)->setAddr(_server.getClientAddr());

	// _output.push(new ApplicationCallback<requestCode::SessionID>((*it)->sessionID(), &Application::ClientLeaveGame));
	GamePool	*associatedPool = (*it)->gamePool();

	associatedPool->input().push(new Callback<GamePool, AGameRequest *>(associatedPool, req, &GamePool::dispatchMessages));

	// (*it)->requestPushInput(req);
	// (*it)->hasJoin(true);
      }
      else
	delete req;
    }
    _server.read(false);
  }


  /////////////////////////
  // Callback Management //
  /////////////////////////

  GamePool		*Manager::findFreeGameSlot()
  {
    pool_list::iterator it = _gamePools.begin();

    while (it != _gamePools.end() && (*it)->full())
      ++it;
    if (it == _gamePools.end())
    {
      _gamePools.push_back(new GamePool(this, _inputFromPools));
      _gamePools.back()->run();
      return (_gamePools.back());
    }
    return *it;
  }

  void			Manager::newGame(Game *game)
  {
    Game::client_list	clients = game->clients();
    GamePool		*pool = findFreeGameSlot();

#if defined(DEBUG)
    Application::log << "Game::Manager::newGame()" << "New Game pushed"  << std::endl;
#endif
    // _games.push_back(game);
    // TODO: Push the game in a selected pool, or create one

    game->parent(pool);
    pool->input().push(new Callback<GamePool, Game *>(pool, game, &GamePool::newGame));

    for (Game::client_list::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      // (*it)->inUse(true);
      (*it)->gamePool(pool);
      _gameClients.push_back(*it);
    }
  }

  void			Manager::updateCallback()
  {
    ICallbacks		*cb;

    while ((cb = _input.pop(false)) != 0)
    {
      (*cb)();
      delete cb;
    }
    while ((cb = _inputFromPools.pop(false)) != 0)
    {
      (*cb)();
      delete cb;
    }
  }


  /////////////
  // Routine //
  /////////////
  void			Manager::routine(Manager *self)
  {

    while (self->_active)
    {
      struct	timeval	def;

      def.tv_sec = 1;
      def.tv_usec = 0;
      self->_monitor.setOption(net::streamManager::TIMEOUT, def);

      self->_monitor.run(); /* Surcouche du select() */
      self->updateCallback();
      if (self->_server.read())
      {
  	try
  	{
	  self->dispatchMessages();
  	}
  	catch (net::Exception &e)
  	{
  	  Application::log << "Error " << e.what() << "in Manager::routine."  << std::endl;
  	}
      }
    }
  }

  net::UdpServer	&Manager::server()
  {
    return (_server);
  }

  void			Manager::cancelGame(const Game *game)
  {
    _gameClients.remove_if(PredicateClients(game->clients()));
    _output.push(new ApplicationCallback<const Game *>(game, &Application::cancelGame));
#if defined(DEBUG)
    Application::log << "game::Manager::cancelGame() - Game " << game
	      << " has just been cancelled" ;
#endif // !DEBUG
  }

  void			Manager::endGame(const Game *game)
  {
    _gameClients.remove_if(PredicateClients(game->clients()));
    _output.push(new ApplicationCallback<const Game *>(game, &Application::endGame));
#if defined(DEBUG)
    Application::log << "game::Manager::endGame() - Game " << game
	      << " has just been ended" ;
#endif // !DEBUG
  }

  ///////////////
  // Predicate //
  ///////////////

  Manager::predicate::predicate(const requestCode::SessionID id):
    _id(id)
  {

  }

  Manager::predicate::~predicate()
  {

  }

  bool		Manager::predicate::operator()(const Client *rhs)
  {
#if defined(DEBUG)
    Application::log << _id << " || " << rhs->sessionID()  << std::endl;
#endif
    return (_id == rhs->sessionID());
  }

  Manager::PredicateClients::PredicateClients(const client_list &clients):
    _clients(clients)
  {

  }

  Manager::PredicateClients::~PredicateClients()
  {

  }

  bool		Manager::PredicateClients::operator()(const Client *rhs)
  {
    return (std::find(_clients.begin(), _clients.end(), rhs) != _clients.end());
  }

}


///////////////////
// Previous code //
///////////////////



// void		Manager::update()
// {
//   bool	asleftplayer = false;

// #if defined(DEBUG)
//   Application::log << "Manager::Update"  << std::endl;
// #endif
//   if (!_games.empty())
//   {
//     Game *game = _games.front();

//     if (game->launchGameTime() == 0)
//     {
//       for (std::list<game::Client *>::iterator it = game->clients().begin(); it != game->clients().end(); it++)
//       {
// 	(*it)->alive(false);
// 	(*it)->hasLeft(true);
// 	_output.push(new ApplicationCallback<requestCode::SessionID>((*it)->sessionID(), &Application::ClientLeaveGame));
//       }
//       _output.push(new ApplicationCallback<game::Game *>(game, &Application::endGame));
//       _games.pop_front();
//       _server.monitor(true, false);
//       return;
//     }
//     for (std::list<game::Client *>::iterator it = game->clients().begin(); it != game->clients().end(); it++)
//       if ((*it)->hasJoin() == false)
//       {
// 	game->timer().tv_usec = rtype::Env::getInstance().game.gameDelay;
// 	game->launchGametime(game->launchGameTime() - 1);
// 	_server.monitor(true, false);
// 	return;
//       }
//     _games.pop_front();
//     if (!game->clients().empty())
//     {
//       asleftplayer = game->update();
//       _games.push_back(game);
//     }
//     else
//     {
//       _output.push(new ApplicationCallback<Game *>(game, &Application::endGame));
//     }
//   }

//   if (asleftplayer == true)
//   {
//     client_list::iterator it = _gameClients.begin();

//     for (; it != _gameClients.end();)
//     {
//       if ((*it)->hasLeft())
//       {
// 	game::Client	*c = *it;

// 	it = _gameClients.erase(it);
// 	_output.push(new ApplicationCallback<requestCode::SessionID>(c->sessionID(), &Application::ClientLeaveGame));
// 	delete c;
//       }
//       else
// 	++it;
//     }
//   }
//   _server.monitor(true, true);
// }

// void			Manager::routine(Manager *self)
// {
//   self->_clock.start();
//   while (self->_active)
//   {
//     self->_clock.update();
//     self->updateGameClocks(self->_clock.getElapsedTime());
//     if (!self->_games.empty())
// 	self->_monitor.setOption(net::streamManager::TIMEOUT, self->_games.front()->timer());
//     else
//     {
// 	struct	timeval	def;
// 	def.tv_sec = 1;
// 	def.tv_usec = 0;
// 	self->_monitor.setOption(net::streamManager::TIMEOUT, def);
//     }
//     self->_monitor.run(); /* Surcouche du select() */
//     self->_clock.update();
//     self->updateGameClocks(self->_clock.getElapsedTime());
//     self->updateCallback();
//     if (self->_server.read() || self->_server.write())
//     {
// 	try
// 	{
// 	  if (self->_server.read())
// 	    self->readData();
// 	  if (self->_server.write())
// 	    self->writeData();
// 	}
// 	catch (net::Exception &e)
// 	{
// 	  Application::log << "Error " << e.what() << "in Manager::routine."  << std::endl;
// 	}
//     }
//     if (self->_monitor.isTimeout())
//     {
// 	self->update();
//     }
//   }
// }

// void			Manager::writeData()
// {
//   client_list::iterator	it;

//   for (it = _gameClients.begin();
// 	 it != _gameClients.end();
// 	 it++)
//   {
//     _server.setClientAddr((*it)->getAddr());
//     while (ARequest *req = (*it)->requestPopOutput())
//     {
// 	std::vector<cBuffer::Byte> buf;

// 	buf = Protocol::product(*req);
// 	_server.writeIntoBuffer(buf, buf.size());
// 	_server.send();
//     }
//   }
//   _server.monitor(true, false);
//   _server.write(false);
// }

// void			Manager::updateGameClocks(Clock::clock_time time)
// {
//   std::deque<Game *>::iterator	it;

//   for (it = _games.begin(); it != _games.end(); it++)
//   {
//     (*it)->timer().tv_usec -= time;
//     if ((*it)->timer().tv_usec < 0)
// 	(*it)->timer().tv_usec = 0;
//   }
// }

