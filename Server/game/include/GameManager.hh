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
    typedef void(*request_callback)(ARequest *, Client *, Manager *);
    typedef Thread::EventQueue<ICallbacks *>			input_event;
    typedef Thread::EventQueue<IApplicationCallbacks *>		output_event;
    typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;
    typedef std::list<Client *>					client_vect;
    typedef std::deque<Game *>					game_list;

  public:
    Manager(input_event &input, output_event &output);
    ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::UDP_SERVER_PORT);
    void	run();
    void	join();
    void	stop();

  private:
    static void		routine(Manager *);
    bool		getRequest(std::vector<cBuffer::Byte> &buf,
				   AGameRequest *&request);

  public:
    void		newGame(Game *);

  private:
    void		update();
    void		updateCallback();
    void		readData();
    void		writeData();
    void		updateGameClocks(Clock::clock_time time);

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
    bool				_active;
    Threads<void (*)(Manager *)>	_th;
    Clock				_clock;
    game_list				_games;
    input_event				&_input;
    output_event			&_output;
    net::UdpServer			_server;
    net::streamManager			_monitor;
    client_vect				_gameClients;
    // request_callback_map		_requestCallback;

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
