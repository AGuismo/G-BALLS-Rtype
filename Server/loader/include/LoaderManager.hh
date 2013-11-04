#ifndef LOADER_MANAGER_H_
# define LOADER_MANAGER_H_

#include	"Threads.hpp"
#include	"CheckFileAbstract.h"
#include	"DynamicAbstract.h"
#include	"myLibrary.h"

namespace	botLoader
{
  class		Manager
  {
  public:
    Manager();
    ~Manager();

  public:
    void	initialize(std::string &);
    void	run();

  private:
    static void	routine(Manager *);
    /*ICI ROUTINE PAR LA SUITE MF*/
  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    ICheckFileAbstract			*_checkFile;
    DynamicAbstract			*_dynLoader;
    std::map<std::string, UPDATE>	*_upList;
    Threads<void (*)(Manager *)>	_th;
  };

}

#endif /* LOADER_MANAGER_H_ */
