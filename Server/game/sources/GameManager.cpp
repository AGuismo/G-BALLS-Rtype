#include	<iostream>
#include	<algorithm>
#include	"Game.h"
#include	"ICallbacks.hh"
#include	"GameManager.hh"
#include	"Client.hh"
#include	"AGameRequest.hh"
#include	"sys.hh"
#include	"Bind.hpp"
#include	"NetException.h"
#include	"ClientAccepted.h"
#include	"Protocol.hpp"
#include	"GameClient.hh"
#include	"Callback.hh"
#include	"Application.hh"

namespace	game
{
  Manager::Manager(Manager::input_event &input, Manager::output_event &output) :
    _th(Func::Bind(&Manager::routine, this)), _input(input), _output(output)
  {
    _server.monitor(true, false);
  }

  Manager::~Manager()
  {
    _active = false;
    join();
    for (client_vect::iterator it = _gameClients.begin(); it != _gameClients.end(); ++it)
      delete *it;
    for (game_list::iterator it = _games.begin(); it != _games.end(); ++it)
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
      std::cout << e.what() << std::endl;
      throw net::Exception("Unable to init Game Manager");
    }
  }

  void	Manager::run()
  {
    _active = true;
    _th.run();
#if defined(DEBUG)
    std::cout << "Game manager started..." << std::endl;
#endif
  }

  bool	Manager::getRequest(std::vector<cBuffer::Byte> &buf,
			    AGameRequest *&request)
  {
    AGameRequest			*req;
    int					extracted;

    try
    {
      req = dynamic_cast<AGameRequest *>(Protocol::consume(buf, extracted));
      if (req == 0)
	throw Protocol::ConstructRequest("Request is not a GameRequest");
    }
    catch (Protocol::ConstructRequest &e)
    {
#if defined(DEBUG)
      std::cerr << "Failed to create request: " << e.what() << std::endl;
#endif
      return (false);
    }
    request = req;
    return true;
  }

  void					Manager::readData()
  {
    client_vect::iterator		it;
    std::vector<cBuffer::Byte>		buf;
    AGameRequest			*req;

    _server.recv();
    _server.readFromBuffer(buf, rtype::Env::getInstance().network.maxUDPpacketLength);
#if defined(DEBUG)
    std::cout<< "Manager::readData::buf = " << buf.size() << std::endl;
    for (std::vector<cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); it++)
      std::cout << *it;
#endif
    if ((getRequest(buf, req)) == false)
      return;
    it = std::find_if(_gameClients.begin(), _gameClients.end(), predicate(req->SessionID()));
    if (it != _gameClients.end())
    {
#if defined(DEBUG)
      std::cout << "Client " << (*it)->sessionID() << "send a request of type " << req->code() << std::endl << std::endl;
#endif
      (*it)->setAddr(_server.getClientAddr());
      (*it)->requestPushInput(req);
      (*it)->hasJoin(true);
    }
    _server.read(false);
  }

  void			Manager::writeData()
  {
    client_vect::iterator	it;

    for (it = _gameClients.begin();
	 it != _gameClients.end();
	 it++)
    {
      _server.setClientAddr((*it)->getAddr());
      while (ARequest *req = (*it)->requestPopOutput())
      {
	std::vector<cBuffer::Byte> buf;

	buf = Protocol::product(*req);
	_server.writeIntoBuffer(buf, buf.size());
	_server.send();
      }
    }
    _server.monitor(true, false);
    _server.write(false);
  }

  void			Manager::updateGameClocks(Clock::clock_time time)
  {
    std::deque<Game *>::iterator	it;

    for (it = _games.begin(); it != _games.end(); it++)
    {
      (*it)->timer().tv_usec -= time;
      if ((*it)->timer().tv_usec < 0)
	(*it)->timer().tv_usec = 0;
    }
  }

  void			Manager::newGame(Game *game)
  {
    Game::client_list	clients = game->clients();

#if defined(DEBUG)
    std::cout << "Game::Manager::newGame()" << "New Game pushed" << std::endl;
#endif
    _games.push_back(game);
    for (Game::client_list::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      // (*it)->inUse(true);
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
  }

  void		Manager::update()
  {
    bool	asleftplayer = false;

#if defined(DEBUG)
    std::cout << "Manager::Update" << std::endl;
#endif
    if (!_games.empty())
    {
      Game *game = _games.front();

      if (game->launchGameTime() == 0)
      {
	for (std::list<game::Client *>::iterator it = game->clients().begin(); it != game->clients().end(); it++)
	{
	  (*it)->alive(false);
	  (*it)->hasLeft(true);
	  _output.push(new ApplicationCallback<requestCode::SessionID>((*it)->sessionID(), &Application::ClientLeaveGame));
	}
	_output.push(new ApplicationCallback<game::Game *>(game, &Application::endGame));
	_games.pop_front();
	_server.monitor(true, false);
	return;
      }
      for (std::list<game::Client *>::iterator it = game->clients().begin(); it != game->clients().end(); it++)
	if ((*it)->hasJoin() == false)
	{
	  game->timer().tv_usec = rtype::Env::getInstance().game.gameDelay;
	  game->launchGametime(game->launchGameTime() - 1);
	  _server.monitor(true, false);
	  return;
	}
      _games.pop_front();
      if (!game->clients().empty())
      {
	asleftplayer = game->update();
	_games.push_back(game);
      }
      else
      {
	_output.push(new ApplicationCallback<Game *>(game, &Application::endGame));
      }
    }

    if (asleftplayer == true)
    {
      client_vect::iterator it = _gameClients.begin();

      for (; it != _gameClients.end();)
      {
	if ((*it)->hasLeft())
	{
	  game::Client	*c = *it;

	  it = _gameClients.erase(it);
	  _output.push(new ApplicationCallback<requestCode::SessionID>(c->sessionID(), &Application::ClientLeaveGame));
	  delete c;
	}
	else
	  ++it;
      }
    }
    _server.monitor(true, true);
  }

  void			Manager::stop()
  {
    _active = false;
  }

  void			Manager::routine(Manager *self)
  {
    self->_clock.start();
    while (self->_active)
    {
      self->_clock.update();
      self->updateGameClocks(self->_clock.getElapsedTime());
      if (!self->_games.empty())
	self->_monitor.setOption(net::streamManager::TIMEOUT, self->_games.front()->timer());
      else
      {
	struct	timeval	def;
	def.tv_sec = 1;
	def.tv_usec = 0;
	self->_monitor.setOption(net::streamManager::TIMEOUT, def);
      }
      self->_monitor.run(); /* Surcouche du select() */
      self->_clock.update();
      self->updateGameClocks(self->_clock.getElapsedTime());
      self->updateCallback();
      if (self->_server.read() || self->_server.write())
      {
	try
	{
	  if (self->_server.read())
	    self->readData();
	  if (self->_server.write())
	    self->writeData();
	}
	catch (net::Exception &e)
	{
	  std::cerr << "Error " << e.what() << "in Manager::routine." << std::endl;
	}
      }
      if (self->_monitor.isTimeout())
      {
	self->update();
      }
    }
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
    std::cout << _id << " || " << rhs->sessionID() << std::endl;
#endif
    return (_id == rhs->sessionID());
  }
}
