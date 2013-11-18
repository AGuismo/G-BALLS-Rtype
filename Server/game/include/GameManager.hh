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

# include	<list>
# include	<map>
# include	<vector>
# include	"Threads.hpp"
# include	"Clock.h"
# include	"UdpServer.h"
# include	"streamManager.h"
# include	"Env.hh"
# include	"RequestCode.hh"
# include	"cBuffer.h"
# include	"GameClient.hh"
# include	"Game.h"
# include	"ThreadEvent.hpp"
# include	"Client.hh"

//class	Client;
class	AGameRequest;

using	net::cBuffer;

namespace	game
{
  class Manager
  {
    typedef void(*request_callback)(ARequest *, Client *, Manager *);
    typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;
    typedef std::vector< ::Client *>				client_vect;

  public:
	  Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue<ARequest *> &output);
    ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::UDP_SERVER_PORT);
    void	run();

  private:
    static void	routine(Manager *);
	bool		getRequest(std::vector<cBuffer::Byte> &buf,
		AGameRequest *&request);

  private:
    void		update();
    void		readData();
	void		writeData();

  private:
    void		getGame();
    client_vect::iterator	findSource(net::ClientAccepted *client,
					   std::vector<cBuffer::Byte> &buf,
					   AGameRequest *&request);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private :


  private:
    Threads<void (*)(Manager *)>	_th;
    Clock				_clock;
    std::list<Game *>			_games;
	Thread::EventQueue<ARequest *>		&_input;
	Thread::EventQueue<ARequest *>		&_output; /* what's this ??*/
	net::UdpServer			_server;
    net::streamManager			_monitor;
    client_vect				_gameClients;
    request_callback_map		_requestCallback;

  private:
    class predicate : public std::unary_function< ::Client *, bool>
    {
    public:
      predicate(const requestCode::SessionID id): _id(id) {};
      ~predicate() {};

    public:
      bool		operator()(::Client *rhs) {return (_id == rhs->id());}

    private:
      const requestCode::SessionID	_id;
    };

  };
}

#endif /* GAMEMANAGER_H_ */
