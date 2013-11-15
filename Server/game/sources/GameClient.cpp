#include	"GameClient.hh"
#include	"EventRequest.hh"
#include	"Player.h"
#include	"AliveRequest.h"
#include	"Env.hh"
#include	"ElemRequest.hh"
#include	"Missile.h"

namespace	game
{
  Client::Client():
	  _used(false), _alive(true), _updateToLive(0)
  {
  }
  
  Client::Client(struct sockaddr_in addr) :
	  _used(false), _addr(addr), _alive(true), _updateToLive(0)
  {

  }

  Client::~Client()
  {

  }

  void	Client::update(RequestQueue &p, std::list<::Missile *> &missiles)
  {
	  ARequest *req;
	  bool		move = false;
	  bool		fire = false;

	  do {
		  req = _input.requestPop();
		  if (EventRequest * ev = dynamic_cast<EventRequest *>(req))
		  {
			  if (ev->event() == 0 && !move)
			  {
				  move = true;
				  _player->move(ev->param());
				  p.requestPush(new ElemRequest(requestCode::game::ELEM,
												ev->param(), _player->_dir, _id));
			  }
			  else if (!fire)
			  {
				  missiles.push_back(_player->fire());
				  fire = true;
				  p.requestPush(new ElemRequest(requestCode::game::ELEM,
					  _player->_pos, _player->_dir, 0/* ID du missile ??*/));
			  }
		  }
		  else if (AliveRequest * al = dynamic_cast<AliveRequest *>(req))
			  _updateToLive = -1;
	  } while (req);
	  _updateToLive++;
	  if (_updateToLive == rtype::Env::updateToLive)
		_alive = false;
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
