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

#include	"Threads.hpp"
#include	"Partie.h"
#include	"clock.h"

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

	void		timerSub(struct timeval *a, long b);
  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<void (*)(Manager *)>	_th;
	gameClock						_clock;
	std::list<Partie *>				_games;
  };
}

#endif /* GAMEMANAGER_H_ */
