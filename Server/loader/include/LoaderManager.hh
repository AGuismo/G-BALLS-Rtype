#ifndef LOADER_MANAGER_H_
# define LOADER_MANAGER_H_

#include	"Threads.hpp"

namespace	botLoader
{
  class		Manager
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
    Threads<void (*)(void *), void *>	_th;
  };

}

#endif /* LOADER_MANAGER_H_ */
