#include	"GameClient.hh"
#include	"EventRequest.hh"
#include	"Player.h"
#include	"AliveRequest.h"
#include	"Env.hh"
#include	"ElemRequest.hh"
#include	"DeathRequest.h"
#include	"LeaveRequest.h"
#include	"Missile.h"
#include	"Referee.h"

namespace	game
{
  Client::Client(requestCode::SessionID &id) :
    _player(0), _alive(true), _updateToLive(0), _hasLeft(false),
    _used(false), _hasJoin(false), _id(id)

  {
    std::cout << "game::client created" << std::endl;
  }

  Client::Client(requestCode::SessionID &id, struct sockaddr_in addr) :
    _player(0), _alive(true), _updateToLive(0), _hasLeft(false),
    _used(false), _hasJoin(false),
    _addr(addr), _id(id)
  {
    std::cout << "game::client created" << std::endl;
  }

  Client::~Client()
  {
  }

  void			Client::alive(const bool &state)
  {
    _alive = state;
  }

  bool			Client::alive() const
  {
    return _alive;
  }

  void			Client::hasLeft(const bool &state)
  {
    _hasLeft = state;
  }

  void		Client::update(Game &game)
  {
    ARequest	*req;
    bool	move = false;
    bool	fire = false;

    while ((req = _input.requestPop()) != 0)
      {
	EventRequest	*ev;
	AliveRequest	*al;
	LeaveRequest	*lv;
	if ((ev = dynamic_cast<EventRequest *>(req)))
	  {
		_updateToLive = -1;
	    if (ev->event() == 0 && !move)
	      {
		move = true;
		_player->move(ev->param());
		if (Referee::isCollision(_player, game) || !Referee::isOnScreen(_player))
		  {
		    _alive = false;
		    game.pushRequest(new DeathRequest(_id));
		  }
		else
			game.pushRequest(new ElemRequest(requestCode::game::server::PLAYER,
						   _player->_pos[0], _player->_dir, _player->_id));
	      }
	    else if (!fire)
	      {
		Missile *missile = _player->fire(game, false);
		game.pushMissile(missile);
		fire = true;
		game.pushRequest(new ElemRequest(requestCode::game::server::MISSILE,
						 missile->pos()[0], missile->dir(), missile->id()));
	      }
	  }
	else if ((al = dynamic_cast<AliveRequest *>(req)))
	  {
	    _updateToLive = -1;
	  }
	else if ((lv = dynamic_cast<LeaveRequest *>(req)))
	  {
	    _alive = false;
	    _hasLeft = true;
	    game.pushRequest(new DeathRequest(_player->_id));
	  }
      }
    _updateToLive++;
	if (_updateToLive == rtype::Env::getInstance().game.updateToLive)
      {
	_alive = false;
	_hasLeft = true;
	game.pushRequest(new DeathRequest(_player->_id));
      }
  }

  void	Client::finalize()
  {

  }

  ARequest	*Client::requestPop()
  {
    return (_input.requestPop());
  }

  ARequest	*Client::requestPopOutput()
  {
    return (_output.requestPop());
  }

  void		Client::requestPushInput(ARequest *req)
  {
    _input.requestPush(req);
  }

  void		Client::requestPush(ARequest *req)
  {
    _output.requestPush(req);
  }

  requestCode::SessionID	Client::SessionID() const
  {
    return (_id);
  }

  void				Client::SessionID(const requestCode::SessionID id)
  {
    _id = id;
  }

  void				Client::player(Player *player)
  {
    _player = player;
  }

  Player			*Client::player(void) const
  {
    return (_player);
  }
}
