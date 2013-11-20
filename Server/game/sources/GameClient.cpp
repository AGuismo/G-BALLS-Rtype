#include	"GameClient.hh"
#include	"EventRequest.hh"
#include	"Player.h"
#include	"AliveRequest.h"
#include	"Env.hh"
#include	"ElemRequest.hh"
#include	"DeathRequest.h"
#include	"Missile.h"
#include	"Referee.h"

namespace	game
{
  Client::Client(requestCode::SessionID &id):
    _alive(true), _updateToLive(0), _used(false), _id(id)
  {
  }

  Client::Client(requestCode::SessionID &id, struct sockaddr_in addr) :
    _alive(true), _updateToLive(0), _used(false), _addr(addr), _id(id)
  {

  }

  Client::~Client()
  {

  }

  void			Client::alive(const bool &state)
  {
	  _alive = state;
  }

  void		Client::update(Game &game)
  {
    ARequest	*req;
    bool	move = false;
    bool	fire = false;

    do {
      req = _input.requestPop();
      EventRequest	*ev;
      AliveRequest	*al;
      if ((ev = dynamic_cast<EventRequest *>(req)))
    	{
    	  if (ev->event() == 0 && !move)
    	    {
    	      move = true;
    	      _player->move(ev->param());
			  if (Referee::isCollision(_player, game) || !Referee::isOnScreen(_player))
			  {
				  _alive = false;
				  game.pushRequest(new DeathRequest(_player->_id));
			  }
			  else
    			  game.pushRequest(new ElemRequest(PLAYER,
    					    _player->_pos, _player->_dir, _player->_id));
    	    }
    	  else if (!fire)
    	    {
			  Missile *missile = _player->fire(game);
			  game.pushMissile(missile);
    	      fire = true;
    	      game.pushRequest(new ElemRequest(MISSILE,
    					    missile->pos(), missile->dir(), missile->id()));
    	    }
    	}
      else if ((al = dynamic_cast<AliveRequest *>(req)))
    	_updateToLive = -1;
    } while (req);
    _updateToLive++;
	if (_updateToLive == rtype::Env::updateToLive)
	{
		_alive = false;
		game.pushRequest(new DeathRequest(_player->_id));
	}
// =======
	  // ARequest *req;
	  // bool		move = false;
	  // bool		fire = false;

	  // do {
	  // 	  req = _input.requestPop();
	  // 	  if (EventRequest * ev = dynamic_cast<EventRequest *>(req))
	  // 	  {
	  // 		  if (ev->event() == 0 && !move)
	  // 		  {
	  // 			  move = true;
	  // 			  _player->move(ev->param());
	  // 			  p.requestPush(new ElemRequest(requestCode::game::ELEM,
	  // 											ev->param(), _player->_dir, _id));
	  // 		  }
	  // 		  else if (!fire)
	  // 		  {
	  // 			  missiles.push_back(_player->fire());
	  // 			  fire = true;
	  // 			  p.requestPush(new ElemRequest(requestCode::game::ELEM,
	  // 				  _player->_pos, _player->_dir, 0/* ID du missile ??*/));
	  // 		  }
	  // 	  }
	  // 	  else if (AliveRequest * al = dynamic_cast<AliveRequest *>(req))
	  // 		  _updateToLive = -1;
	  // } while (req);
	  // _updateToLive++;
	  // if (_updateToLive == rtype::Env::updateToLive)
	  // 	_alive = false;
// >>>>>>> 4d98840f25af5e9c6fb3fa37bab928c391c276a3
  }

  void	Client::finalize()
  {

  }

  ARequest	*Client::requestPop()
  {
    return (_input.requestPop());
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

  void				Client::game(Game *game)
  {
    _game = game;
  }

  Game				*Client::game(void) const
  {
    return (_game);
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
