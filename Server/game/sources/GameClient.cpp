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
  Client::Client(requestCode::SessionID &id):
    _alive(true), _updateToLive(0), _used(false), _id(id)
  {
	  std::cout << "game::client created" << std::endl;
  }

  Client::Client(requestCode::SessionID &id, struct sockaddr_in addr) :
    _alive(true), _updateToLive(0), _used(false), _addr(addr), _id(id)
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

  void		Client::update(Game &game)
  {
    ARequest	*req;
    bool	move = false;
    bool	fire = false;

	std::cout << "UPDATING" << std::endl;
    do {
      req = _input.requestPop();
      EventRequest	*ev;
      AliveRequest	*al;
	  LeaveRequest	*lv;
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
    					    _player->_pos[0], _player->_dir, _player->_id));
    	    }
    	  else if (!fire)
    	    {
			  Missile *missile = _player->fire(game, false);
			  game.pushMissile(missile);
    	      fire = true;
    	      game.pushRequest(new ElemRequest(MISSILE,
    					    missile->pos()[0], missile->dir(), missile->id()));
    	    }
    	}
	  else if ((al = dynamic_cast<AliveRequest *>(req)))
		  _updateToLive = -1;
	  else if ((lv = dynamic_cast<LeaveRequest *>(req)))
	  {
		  for (int i = 0; i != 50; i++)
			  std::cout << "LEAVING" << std::endl;
		  _alive = false;
		  game.pushRequest(new DeathRequest(_player->_id));
	  }
    } while (req);
    _updateToLive++;
	if (_updateToLive == rtype::Env::updateToLive)
	{
		_alive = false;
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
