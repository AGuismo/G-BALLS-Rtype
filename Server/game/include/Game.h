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
#include	"Boss.h"

class Event;
class TIMER;
class Referee;
class Missile;

namespace	game
{
  class		Player;
}

class Game
{
public:
  Game(std::list<game::Player *> &players);
  ~Game();
  void	update();
  struct timeval	*getTimer(void)const{ return _timer;};

private:
  void iaUpdate();
  void entityUpdate();
  void missileUpdate();
  void bossUpdate();
  void wallUpdate();

private:
  std::list<game::Player *>	_players;
  std::list<Ia *>		_IA;
  std::list<Entity *>		_objs;
  std::list<Missile *>		_missiles;
  Boss				*_titan;
  struct timeval		*_timer;

  friend class ::Referee;
};
