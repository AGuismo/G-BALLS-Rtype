#ifndef GAMEMANAGER_H_
# define GAMEMANAGER_H_

#include	"Threads.hpp"

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
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<void, Manager *>	_th;
  };
}

#endif /* GAMEMANAGER_H_ */
