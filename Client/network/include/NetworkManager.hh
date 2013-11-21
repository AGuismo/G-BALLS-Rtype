#ifndef NETWORKMANAGER_H_
# define NETWORKMANAGER_H_

#include	"Threads.hpp"

namespace	network
{
  class Manager
  {
  public:
    Manager();
    virtual ~Manager();

  private:
    void	routine();

  public:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<void (Manager::*)()>	_th;
  };
}

#endif /* NETWORKMANAGER_H_ */
