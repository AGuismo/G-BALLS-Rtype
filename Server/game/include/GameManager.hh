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
#include	"Threads.hpp"
#include	"Clock.h"

class	Game;

namespace	game
{
  class Manager
  {
  public:
    Manager();
    ~Manager();

  public:
    void	initialize();
    void	run();

  private:
    static void	routine(Manager *);

  private:
    void		update();

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<void (*)(Manager *)>	_th;
    Clock				_clock;
    std::list<Game *>			_games;
  };
}

#endif /* GAMEMANAGER_H_ */
