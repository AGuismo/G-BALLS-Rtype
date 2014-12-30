#ifndef GAMEMANAGER_H_
# define GAMEMANAGER_H_

//#if defined(WIN32)
//#include <WinSock2.h>
//#include 
//#elif defined(linux)
//#include <sys/time.h>
//#else
//# error "Unsupported operating system"
//#endif

# include	<list>
# include	<map>
# include	<vector>
# include	<ctime>
# include	"Threads.hpp"
//# include	"Clock.h"
# include	"UdpServer.h"
# include	"streamManager.h"
# include	"Env.hh"
# include	"RequestCode.hh"
// # include	"cBuffer.h"
# include	"GameClient.hh"
// # include	"Game.hh"
# include	"ThreadEvent.hpp"

//class	Client;
class	AGameRequest;
class	ICallbacks;
class	IApplicationCallbacks;
using	net::cBuffer;

namespace	game
{
  class	Client;
  class	GamePool;

  class Manager
  {
    typedef Thread::EventQueue<ICallbacks *>			input_event;
    typedef Thread::EventQueue<IApplicationCallbacks *>		output_event;
    typedef std::list<GamePool *>				pool_list;
    typedef std::list<Client *>					client_list;
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
    bool		getRequest(AGameRequest *&request);
    GamePool		*findFreeGameSlot();

  public:
    void		newGame(Game *);
    void		cancelGame(const Game *);
    void		endGame(const Game *);

  public:
    net::UdpServer	&server();

  private:
    void		updateCallback();
    void		dispatchMessages();
    // void		update();
    // void		writeData();
    // void		updateGameClocks(Clock::clock_time time);

  private:
    // void				getGame();
    // void				sessionID(const requestCode::SessionID &);
    // const requestCode::SessionID	&sessionID(void) const;
    // client_list::iterator		findSource(net::ClientAccepted *client,
    // 						   std::vector<cBuffer::Byte> &buf,
    // 						   AGameRequest *&request);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    bool				_active;
    Threads<void (*)(Manager *)>	_th;
    // Clock				_clock;
    // game_list			_games;
    input_event				&_input;
    output_event			&_output;
    input_event				_inputFromPools;
    pool_list				_gamePools;
    client_list				_gameClients;
    net::UdpServer			_server;
    net::streamManager			_monitor;

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

    class PredicateClients : public std::unary_function< const Client *, bool>
    {
    public:
      PredicateClients(const client_list &clients);
      ~PredicateClients();

    public:
      bool		operator()(const Client *rhs);

    private:
      const client_list	_clients;
    };

  };
}

#endif /* GAMEMANAGER_H_ */
