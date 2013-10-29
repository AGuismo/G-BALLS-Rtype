#include	"LoaderManager.hh"

namespace	botLoader
{
  Manager::Manager():
    _th(&Manager::routine, this)
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
    (void)thisPtr;
  }
}
