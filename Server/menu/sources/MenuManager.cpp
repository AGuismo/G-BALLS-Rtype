#include	<iostream>
#include	"MenuManager.hh"
#include	"MenuException.hh"
#include	"sys.hh"
#include	"Client.hh"
#include	"NetException.h"
#include	"AuthRequest.hh"

namespace	menu
{
  Manager::Manager()
  {
    _server.monitor(true, false);
    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;
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

  void	Manager::clientRequest(Client *client)
  {
    ARequest *req = client->requestPop();

    while (req != 0)
      {
	request_callback_map::iterator	it = _requestCallback.find(req->code());

	if (it != _requestCallback.end())
	  it->second(req, client, this);
	delete req;
	req = client->requestPop();
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
#if defined(DEBUG)
	    std::cerr << "Client disconnected(" << *it << ")" << std::endl;
#endif
	    _monitor.unsetMonitor(*client->TcpLayer());
	    it = _clients.erase(it);
	    delete client;
	    continue ;
	  }
	clientRequest(*it);
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

  ///////////////////////
  // Request Modifiers //
  ///////////////////////

  void	Manager::tryConnect(ARequest *req, Client *client, Manager *manager)
  {
    Auth::Connect	*request = dynamic_cast<Auth::Connect *>(req);

    std::cout << request->username() << ":" << request->password() << std::endl;
    (void)client;
    (void)manager;
  }
}
