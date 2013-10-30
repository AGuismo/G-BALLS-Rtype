#include	<iostream>
#include	"sys.hh"
#include	"MenuManager.hh"

namespace	menu
{
  Manager::Manager()
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
    std::cout << "Menu manager started..." << std::endl;
    routine(this);
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
