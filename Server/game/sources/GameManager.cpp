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
	(*it)->game().setAddr(_server.getClientAddr());
	(*it)->game().requestPush(req);
      }
  }

  void			Manager::writeData()
  {
	  client_vect::iterator	it;

	  for (it = _gameClients.begin();
		  it != _gameClients.end();
		  it++)
	  {
		  _server.setClientAddr((*it)->game().getAddr());
		  while (ARequest *req = (*it)->game().requestPop())
		  {
			  std::vector<cBuffer::Byte> buf;

			  buf = Protocol::product(*req);
			  _server.writeIntoBuffer(buf, buf.size());
			  _server.send();
		  }
	  }
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
		try
		{
			if (thisPtr->_server.read())
				thisPtr->readData();
			if (thisPtr->_server.write())
				thisPtr->writeData();
		}
		catch (net::Exception &e)
		{
			std::cerr << "Error " << e.what() << "in Manager::routine." << std::endl;
		}
		thisPtr->update();
      }
  }
}
