#pragma once

#if defined(WIN32)
#include <WinSock2.h>
#include <time.h>
#elif defined(linux)
#include <sys/time.h>
#else
# error "Unsupported operating system"
#endif

#include	<vector>
#include	<list>
#include	"types.hh"
#include	"GameClient.hh"

class Event;
class TIMER;
class Referee;
class Missile;
class Entity;
class Ia;
class Boss;

namespace	game
{
  class		Player;
}

typedef	Ruint16	ID;

class Game
{
public:
  Game(std::list<game::Client *> &players);
  ~Game();
  void	update();
  struct timeval	*getTimer(void)const{ return _timer;};
  ID   &UniqueId();

private:
  void iaUpdate();
  void entityUpdate();
  void missileUpdate();
  void bossUpdate();
  void wallUpdate();
  void playerUpdate();
  void DispatchRequest();

private:
  std::list<game::Client *>	_players;
  std::list<Ia *>		_IA;
  std::list<Entity *>		_objs;
  std::list<Missile *>		_missiles;
  Boss				*_titan;
  struct timeval		*_timer;
  RequestQueue		_toSend;
  ID				incremental;

  friend class ::Referee;
};
