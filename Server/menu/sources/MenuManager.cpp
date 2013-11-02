#include	<iostream>
#include	"MenuException.hh"
#include	"sys.hh"
#include	"MenuManager.hh"
#include	"Client.hh"
#include	"NetException.h"

namespace	menu
{
  Manager::Manager()
  {
    _server.monitor(true, false);
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
	Client	*client = new Client(_server.accept());

	// #if defined(DEBUG)
	// log::log << log::time() << "Client connected(" << *it << ")" << std::endl;
	// #endif
	_clients.push_back(client);
	_monitor.setMonitor(*(client->TcpLayer()));
      }
  }

  void	Manager::updateClients()
  {
    std::vector<Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end();)
      {
	(*it)->update();
	if ((*it)->isTCPDisconnected())
	  {
	    Client	*client = *it;
	    // #if defined(DEBUG)
	    // log::log << log::time() << "Client disconnected(" << *it << ")" << std::endl;
	    // #endif
	    _monitor.unsetMonitor(*client->TcpLayer());
	    it = _clients.erase(it);
	    delete client;
	    continue ;
	  }
	++it;
      }
  }

  void	Manager::routine(Manager *thisPtr)
  {
    while (true)
      {
	thisPtr->_monitor.run();
	thisPtr->checkNewClient();
	thisPtr->updateClients();
      }
  }
}
