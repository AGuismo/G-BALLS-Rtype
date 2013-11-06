#include	<iostream>
#include	"GameManager.hh"
#include	"sys.hh"
#include	"Bind.hpp"
#include	"NetException.h"
#include	"ClientAccepted.h"

namespace	game
{
  Manager::Manager():
    _th(Func::Bind(&Manager::routine, this))
  {
	  _server.monitor(true, true);
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
		  throw net::Exception("Unable to init Menu Manager");
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
		
      }
  }

  Client	*Manager::readData()
  {
	  std::vector<Client *>::iterator	it;
	  net::ClientAccepted				*client;

	  client = _server.recv();
	  for (it = _clients.begin(); it != _clients.end();)
	  {
		  if (client->_addr.sin_addr.s_addr == (*it)->TcpLayer()->_addr.sin_addr.s_addr)
		  {
			  /*Client already identified*/
			  delete (*it)->TcpLayer();
			  (*it)->TcpLayer(client);
			  return *it;
		  }
		++it;
	  }
	  _clients.push_back(new Client(client));

	  return *(_clients.end());
  }

  void		Manager::routine(Manager *thisPtr)
  {
	clock_time			time;
	timeval				t;
	Client				*client;

	thisPtr->_clock.start();
	while (true)
		{
		thisPtr->_clock.update();
		
		thisPtr->_monitor.run();
		
		thisPtr->_clock.update();
		time = thisPtr->_clock.getElapsedTime();
		t.tv_sec = time / 1000000;
		t.tv_usec = time % 1000000;
		thisPtr->_monitor.setOption(net::streamManager::TIMEOUT, t);
		
		if (thisPtr->_server.read())
			client = thisPtr->readData();
		/*traitement de la requete*/
		thisPtr->update();
		//sys::sleep(1);
		}
  }

}
