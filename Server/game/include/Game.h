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
  Game(std::list<game::Client *> &players);
  ~Game();
  void	update();
  ID   &UniqueId();
  void	pushMissile(Missile *missile);
  void	pushRequest(ARequest *req);
  typedef std::list<game::Client *>	client_list;
  void	randBonnus(Entity &a);
  void	timer(struct timeval t);
  struct timeval &timer();

private:
  void iaUpdate();
  void entityUpdate();
  void missileUpdate();
  void bossUpdate();
  void wallUpdate();
  void playerUpdate();
  void bonusUpdate();
  void DispatchRequest();
  void popIA();
  void pushBoss();

private:
  std::list<game::Client *>	_players;
  std::list<Ia *>		_IA;
  std::list<Entity *>		_objs;
  std::list<Missile *>		_missiles;
  std::list<game::ABonus *>		_bonus;
  Boss				*_titan;
  game::Clock		_clock;
  struct timeval	_timer;
  RequestQueue		_toSend;
  ID				incremental;

  friend class ::Referee;
};
