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
// # include	"cBuffer.h"
# include	"GameClient.hh"
# include	"Game.h"
# include	"ThreadEvent.hpp"

//class	Client;
class	AGameRequest;
class	ICallbacks;

using	net::cBuffer;

namespace	game
{
  class	Client;

  class Manager
  {
    typedef Thread::EventQueue<ICallbacks *>	input_event;
    typedef Thread::EventQueue<ICallbacks *>	output_event;
    typedef void(*request_callback)(ARequest *, Client *, Manager *);
    typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;
    typedef std::list<Client *>			client_vect;

  public:
    Manager(input_event &input, output_event &output);
    ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::UDP_SERVER_PORT);
    void	run();

  private:
    static void		routine(Manager *);
    bool		getRequest(std::vector<cBuffer::Byte> &buf,
				   AGameRequest *&request);

  private:
    void		update();
    void		readData();
    void		writeData();

  private:
    void				getGame();
    void				sessionID(const requestCode::SessionID &);
    const requestCode::SessionID	&sessionID(void) const;
    client_vect::iterator		findSource(net::ClientAccepted *client,
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
    input_event				&_input;
    output_event			&_output;
    net::UdpServer			_server;
    net::streamManager			_monitor;
    client_vect				_gameClients;
    request_callback_map		_requestCallback;

  private:
    class predicate : public std::unary_function< Client *, bool>
    {
    public:
      predicate(const requestCode::SessionID id);
      ~predicate();

    public:
      bool		operator()(const Client *rhs);

    private:
      const requestCode::SessionID	_id;
    };

  };
}

#endif /* GAMEMANAGER_H_ */
