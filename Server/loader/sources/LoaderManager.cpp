#include	"LoaderManager.hh"

namespace	botLoader
{
  Manager::Manager():
    _th(&Manager::routine, (void *)0)
  {

  }

  Manager::~Manager()
  {

  }

  void	Manager::initialize()
  {

  }

  void	Manager::run()
  {
    _th.run();
  }

  void	Manager::routine(Manager *thisPtr)
  {

  }
}
