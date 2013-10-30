#include	<iostream>
#include	"sys.hh"
#include	"LoaderManager.hh"

namespace	botLoader
{
  Manager::Manager():
    _th(&Manager::routine, this)
  {

  }

  Manager::~Manager()
  {
    _th.cancel();
  }

  void	Manager::initialize()
  {

  }

  void	Manager::run()
  {
    _th.run();
    std::cout << "Loader manager started..." << std::endl;
  }

  void	Manager::routine(Manager *thisPtr)
  {
    (void)thisPtr;
    while (true)
      {
	sys::sleep(1);
      }
  }
}
