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
    int	routine();

  public:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Threads<int (Manager::*)()>	_th;
  };
}

#endif /* NETWORKMANAGER_H_ */
