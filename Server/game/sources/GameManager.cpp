#include	<iostream>
#include	"GameManager.hh"
#include	"sys.hh"
#include	"Bind.hpp"

namespace	game
{
  Manager::Manager():
    _th(Func::Bind(&Manager::routine, this))
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
    std::cout << "Game manager started..." << std::endl;
  }

  void		Manager::update()
  {
    std::list<Game *>::iterator it;
    // clock_time			time;

    _clock.start();
    while (true)
      {
	_clock.update();
	/*SELECT*/
	_clock.update();
	// time = _clock.getElapsedTime();
	for (it = _games.begin();
	     it != _games.end();
	     ++it)
	  {

	  }
      }
  }

  void		Manager::routine(Manager *thisPtr)
  {
    thisPtr->update();
  }

}
