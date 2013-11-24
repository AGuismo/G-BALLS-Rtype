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
#include	"Clock.h"
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
  class		ABonus;
}

typedef	Ruint16	ID;

class Game
{
public:
  typedef std::list<game::Client *>	client_list;
public:
  Game(std::list<game::Client *> &players);
  ~Game();
  bool	update();
  ID   &UniqueId();
  void	pushMissile(Missile *missile);
  void	pushRequest(ARequest *req);
  void	randBonnus(Entity &a);
  void	timer(struct timeval t);
  struct timeval &timer();
  client_list	&clients();

private:
  void iaUpdate();
  void entityUpdate();
  void missileUpdate();
  void bossUpdate();
  void wallUpdate();
  bool playerUpdate();
  void bonusUpdate();
  void DispatchRequest();
  void popIA();
  void popWall();

private:
  client_list	_players;
  std::list<Ia *>		_IA;
  std::list<Entity *>		_objs;
  std::list<Missile *>		_missiles;
  std::list<game::ABonus *>	_bonus;
  std::list<Boss *>		_titans;
  Boss				*_titan;
  game::Clock		_clock;
  struct timeval	_timer;
  RequestQueue		_toSend;
  ID				incremental;

  friend class ::Referee;
};
