#include	<iostream>
#include	<algorithm>
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

namespace	game
{
  Manager::Manager(Manager::input_event &input, Manager::output_event &output) :
    _th(Func::Bind(&Manager::routine, this)), _input(input), _output(output)
  {
    _server.monitor(true, false);
  }

  Manager::~Manager()
  {
    _th.cancel();
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
    _th.run();
    std::cout << "Game manager started..." << std::endl;
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
	std::cout << "Manager::readData::buf = " << buf.size() << std::endl;
	for (std::vector<cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); it++)
      std::cout << *it;
    if ((getRequest(buf, req)) == false)
      return;
    it = std::find_if(_gameClients.begin(), _gameClients.end(), predicate(req->SessionID()));
    if (it != _gameClients.end())
	{
		(*it)->setAddr(_server.getClientAddr());
		(*it)->requestPushInput(req);
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
			std::cout << "A Request is just sent" << std::endl;
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
		(*it)->inUse(true);
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
	  std::cout << "Manager::Update" << std::endl;
	  if (!_games.empty())
	  {
		  Game *game = _games.front();

		  _games.pop_front();
		  if (!game->clients().empty())
		  {
			  game->update();
			  _games.push_back(game);
			  std::cout << "Client::size = " << game->clients().size() << std::endl;
		  }
		  else
			delete game;
	  }
  }

  void			Manager::routine(Manager *self)
  {
	  self->_clock.start();
	  while (true)
	  {
		  self->_clock.update();
		  self->updateGameClocks(self->_clock.getElapsedTime());
		  if (!self->_games.empty())
		  {
			  //std::cout << "Selecting for " << self->_games.front()->timer().tv_sec << " sec and " << self->_games.front()->timer().tv_usec << std::endl;
			  self->_monitor.setOption(net::streamManager::TIMEOUT, self->_games.front()->timer());
		  }
		  else
			  self->_monitor.unsetOption(net::streamManager::TIMEOUT);
		  //std::cout << "selecting ..." << std::endl;
		  self->_monitor.run(); /* Surcouche du select() */
		  //std::cout << "Done ..." << std::endl;
		  self->_clock.update();
		  self->updateGameClocks(self->_clock.getElapsedTime());
		  self->_clock.getElapsedTime();
		  self->updateCallback();
		  if (self->_server.read() || self->_server.write())
		  {
			  //std::cout << "Action to do" << std::endl;
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
		  else
		  {
			  //std::cout << "Auto Exit" << std::endl;
			  self->update();
			  self->_server.monitor(true, true);
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
    return (_id == rhs->SessionID());
  }
}
