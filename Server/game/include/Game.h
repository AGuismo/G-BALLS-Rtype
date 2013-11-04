#pragma once

#if defined(WIN32)
#include <WinSock2.h>
#include <time.h>
#elif defined(linux)
#include <sys/time.h>
/*#else
  # error "Unsupported operating system"*/
#endif

#include	<vector>
#include	<list>
#include	"IA.h"
#include	"Player.h"
#include	"Referee.h"
#include	"Missile.h"
#include	"Boss.h"

class Event;
class TIMER;
class Referee;

class Game
{
public:
  Game(std::list<Player *> players);
  ~Game();
  void	update();
  struct timeval	*getTimer(void)const{ return _timer;};
private:
  std::list<Player *>	_players;
  std::list<Ia *>		_IA;
  std::list<Entity *>	_objs;
  std::list<Missile *> _missiles;
  Boss				*_titan;
  struct timeval		*_timer;

  friend Referee;
};
