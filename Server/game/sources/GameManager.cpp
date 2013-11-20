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

  void		Manager::update()
  {
    std::list<Game *>::iterator it;

    for (it = _games.begin();
	 it != _games.end();
	 ++it)
      {
	(*it)->update();
      }
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
    for (std::vector<cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); it++)
      std::cout << *it;
    if ((getRequest(buf, req)) == false)
      return;
    it = std::find_if(_gameClients.begin(), _gameClients.end(), predicate(req->SessionID()));
    if (it != _gameClients.end())
      {
	(*it)->setAddr(_server.getClientAddr());
	(*it)->requestPush(req);
      }
  }

  void			Manager::writeData()
  {
    client_vect::iterator	it;

    for (it = _gameClients.begin();
	 it != _gameClients.end();
	 it++)
      {
	_server.setClientAddr((*it)->getAddr());
	while (ARequest *req = (*it)->requestPop())
	  {
	    std::vector<cBuffer::Byte> buf;

	    buf = Protocol::product(*req);
	    _server.writeIntoBuffer(buf, buf.size());
	    _server.send();
	  }
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

  void			Manager::routine()
  {
    clock_time		time;
    timeval		t;

    _clock.start();
    while (true)
      {
	_clock.update();

	t.tv_sec = 0;
	t.tv_usec = 500000;

	_monitor.setOption(net::streamManager::TIMEOUT, t);

	_monitor.run(); /* Surcouche du select() */

	_clock.update();
	time = _clock.getElapsedTime();
	t.tv_sec = time / 1000000;
	updateCallback();
	try
	  {
	    if (_server.read())
	      readData();
	    if (_server.write())
	      writeData();
	  }
	catch (net::Exception &e)
	  {
	    std::cerr << "Error " << e.what() << "in Manager::routine." << std::endl;
	  }
	update();
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
