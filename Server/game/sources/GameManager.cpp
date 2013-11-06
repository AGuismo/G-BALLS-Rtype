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
  Manager::Manager():
    _th(Func::Bind(&Manager::routine, this))
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
    // clock_time			time;

    _clock.update();
    /*SELECT*/
    _clock.update();
    // time = _clock.getElapsedTime();
    for (it = _games.begin();
	 it != _games.end();
	 ++it)
      {

      }
  }

  std::vector<Client *>::iterator	Manager::findSource(net::ClientAccepted *client,
							    std::vector<cBuffer::Byte> &buf,
							    AGameRequest *&request)
  {
    AGameRequest			*req;
    int					extracted;

    (void)client;
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
	return (_gameClients.end());
      }
    request = req;
    return (std::find_if(_gameClients.begin(), _gameClients.end(), predicate(req->SessionID())));
  }

  void					Manager::readData()
  {
    client_vect::iterator		it;
    net::ClientAccepted			*client;
    std::vector<cBuffer::Byte>		buf;
    AGameRequest			*req;

    client = _server.recv();
    _server.readFromBuffer(buf, rtype::Env::getInstance().network.maxUDPpacketLength);
    if ((it = findSource(client, buf, req)) == _gameClients.end())
      return ;
    (void)req;
    // 	if (client->_addr.sin_addr.s_addr == (*it)->game()->TcpLayer()->_addr.sin_addr.s_addr)
    // 	  {
    // 	    /*Client already identified*/
    // 	    delete (*it)->TcpLayer();
    // 	    (*it)->TcpLayer(client);
    // 	    return *it;
    // 	  }
    // 	++it;
    //   }
    // _clients.push_back(new Client(client));

    // return *(_clients.end());
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
	thisPtr->_monitor.run();

	thisPtr->_clock.update();
	time = thisPtr->_clock.getElapsedTime();
	t.tv_sec = time / 1000000;
	t.tv_usec = time % 1000000;

	if (thisPtr->_server.read())
	  thisPtr->readData();
	/*traitement de la requete*/
	thisPtr->update();
	// sys::sleep(1);
      }
  }

}
