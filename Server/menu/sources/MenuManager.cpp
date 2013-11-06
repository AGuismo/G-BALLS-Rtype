#include	<iostream>
#include	"MenuManager.hh"
#include	"MenuException.hh"
#include	"sys.hh"
#include	"Client.hh"
#include	"NetException.h"
#include	"AuthRequest.hh"
#include	"ServerRequest.hh"

namespace	menu
{
  Manager::Manager()
  {
    _server.monitor(true, false);
    _requestCallback[requestCode::auth::CONNECT] = &tryConnect;

    _requestCallback[requestCode::party::CLI_START] = &launchGame;
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
	::Client	*client = new ::Client(_server.accept());

	_clients.push_back(client);
	_monitor.setMonitor(*(client->menu().TcpLayer()));
      }
  }

  void	Manager::clientRequest(::Client *client)
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

  void	Manager::updateClients()
  {
    std::vector< ::Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end();)
      {
<<<<<<< HEAD
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
=======
	(*it)->update();
	if ((*it)->menu().isTCPDisconnected())
	  {
	    ::Client	*client = *it;
#if defined(DEBUG)
	    std::cerr << "Client disconnected(" << *it << ")" << std::endl;
#endif
	    _monitor.unsetMonitor(*client->menu().TcpLayer());
	    it = _clients.erase(it);
	    delete client;
	    continue ;
	  }
	clientRequest(*it);
	(*it)->finalize();
	++it;
>>>>>>> 3fd9e96e5ef348cc08a6779737bfcd768b5a9ca2
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

  void	Manager::tryConnect(ARequest *req, ::Client *client, Manager *manager)
  {
    Auth::Connect	*request = dynamic_cast<Auth::Connect *>(req);

#if defined(DEBUG)
    std::cout << request->username() << ":" << request->password() << std::endl;
#endif
    (void)manager;
    if (!client->menu().authenticated())
      {
#if defined(DEBUG)
	std::cout << client << ": Authentication succeed" << std::endl;
#endif
	client->menu().username(request->username());
	client->menu().password(request->password());
	client->menu().authenticated(true);
	client->requestPush(new ServerRequest(requestCode::server::OK));
	// client->requestPush(new SessionRequest(Session::Unique()));
      }
    else
      {
#if defined(DEBUG)
	std::cout << client << ": Authentication failed" << std::endl;
#endif
	client->requestPush(new ServerRequest(requestCode::server::FORBIDDEN));
      }
    delete req;
  }

  void	Manager::launchGame(ARequest *req, ::Client *client, Manager *manager)
  {
    (void)client;
    (void)manager;
    delete req;

  }
}
