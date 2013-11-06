#ifndef GAMEMANAGER_H_
# define GAMEMANAGER_H_

#if defined(WIN32)
#include <WinSock2.h>
#include <time.h>
#elif defined(linux)
#include <sys/time.h>
#else
# error "Unsupported operating system"
#endif

#include	<list>
#include	<map>
#include	"Threads.hpp"
#include	"Clock.h"
#include	"UdpServer.h"
#include	"streamManager.h"
#include	"Client.hh"
#include	"ARequest.hh"
#include	"Env.hh"

class	Game;

namespace	game
{
  class Manager
  {
	  typedef void(*request_callback)(ARequest *, Client *, Manager *);
	  typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;

  public:
    Manager();
    ~Manager();

  public:
	  void	initialize(unsigned short int port = rtype::Env::UDP_SERVER_PORT);
    void	run();

  private:
    static void	routine(Manager *);

  private:
    void		update();
	Client		*readData();

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<void (*)(Manager *)>	_th;
    Clock						_clock;
    std::list<Game *>			_games;
	
	net::UdpServer				_server;
	net::streamManager			_monitor;
	std::vector<Client *>		_clients;
	request_callback_map		_requestCallback;

  };
}

#endif /* GAMEMANAGER_H_ */
