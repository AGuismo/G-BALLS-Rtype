#include	<iostream>
#include	<algorithm>
#include	"GameManager.hh"
#include	"Client.hh"
#include	"AGameRequest.hh"
#include	"sys.hh"
#include	"Bind.hpp"
#include	"NetException.h"
#include	"ClientAccepted.h"
#include	"Protocol.hpp"

namespace	game
{
	Manager::Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue<ARequest *> &output) :
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
	if (it == _gameClients.end())
	{
		_gameClients.push_back(new Client(_server.getClientAddr()));
		it = _gameClients.end();
	}
	else
		(*it)->setAddr(_server.getClientAddr());
	(*it)->requestPush(req);
  }


  void			Manager::routine(Manager *thisPtr)
  {
    clock_time		time;
    timeval		t;

    thisPtr->_clock.start();
    while (true)
      {
		thisPtr->_clock.update();

		t.tv_sec = 0;
		t.tv_usec = 500000;

		thisPtr->_monitor.setOption(net::streamManager::TIMEOUT, t);

		thisPtr->_monitor.run(); /* Surcouche du select() */

		thisPtr->_clock.update();
		time = thisPtr->_clock.getElapsedTime();
		t.tv_sec = time / 1000000;
		if (thisPtr->_server.read())
			thisPtr->readData();
		thisPtr->update();
      }
  }
}
