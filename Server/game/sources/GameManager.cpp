#include	<iostream>
#include	"sys.hh"
#include	"Bind.hpp"
#include	"GameManager.hh"

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

  void	Manager::routine(Manager *thisPtr)
  {
	std::list<Partie *>::iterator it;
	clock_time						time;

	(void)thisPtr;
	_clock.start();
	while (true)
	{
		_clock.update();
		/*SELECT*/
		_clock.update();
		time = _clock.getElapsedTime();
		for (it = thisPtr->_games.begin();
			 it != thisPtr->_games.end();
			 it++)
		{
			
		}
	}
  }

}
