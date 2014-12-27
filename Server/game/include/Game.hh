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

class	Event;
class	TIMER;

namespace	net
{
  class		UdpServer;
}

typedef	Ruint16	ID;
namespace game
{
  class	GamePool;
  class	Ia;
  class	Boss;
  class	Referee;
  class	Missile;
  class	Entity;
  class	Player;
  class	ABonus;

  class Game
  {
  public:
    enum Status
      {
	NONE = 0,
	WAITING_PLAYER = 1,
	IN_GAME = 2,
	FINISHED = 4,
	CANCELED = 8
      };

    typedef std::list<Client *>			client_list;
    typedef std::list<Ia *>			ia_list;
    typedef std::list<Entity *>			entity_list;
    typedef std::list<Missile *>		missile_list;
    typedef std::list<ABonus *>			bonus_list;
    typedef std::list<Boss *>			boss_list;

  public:
    Game(std::list<Client *> &players);
    ~Game();

    void		pushMissile(Missile *missile);
    void		pushRequest(ARequest *req);
    void		randBonnus(Entity &a);

    ID				&UniqueId();
    void			timer(struct timeval t);
    struct timeval		&timer();
    const struct timeval	&timer() const;
    client_list			&clients();
    const client_list		&clients() const;
    bool			success() const;
    Status			status() const;
    void			parent(GamePool *parent);
    GamePool			*gamePool() const;

    bool		update();
    void		prepareGame();

  private:
    void		iaUpdate();
    void		entityUpdate();
    void		missileUpdate();
    void		bossUpdate();
    void		wallUpdate();
    bool		playerUpdate();
    void		bonusUpdate();
    void		popIA();
    void		popWall();

    void		sendUpdates();
    void		send(const ARequest &req);

    void		cancelGame();
    void		endGame();
    void		updateGame();
    void		waitingForPlayers();

  private:
    client_list			_clients;
    ia_list			_IA;
    entity_list			_objs;
    missile_list		_missiles;
    bonus_list			_bonus;
    boss_list			_titans;
    Boss			*_titan;
    bool			_success;

    GamePool			*_parent;
    game::Clock			_clock;
    struct timeval		_timer;
    int				_attempsClientConfirmation;
    ID				_incremental;
    Status			_status;
    RequestQueue		_toSend;

    friend class Referee;
  };
}
