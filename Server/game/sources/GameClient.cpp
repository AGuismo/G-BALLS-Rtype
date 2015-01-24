// LibProtocol
#include	"AliveRequest.hh"
#include	"ElemRequest.hh"
#include	"DeathRequest.hh"
#include	"LeaveRequest.hh"

// LibReferee
#include	"Player.hh"

// Module
#include	"GamePool.hh"
#include	"Env.hh"
#include	"GameClient.hh"
#include	"Game.hh"
#include	"Application.hh" // log purpose



namespace	game
{
  Client::Client(requestCode::SessionID id) :
    _alive(true), _updateToLive(0), _hasLeft(false),
    _hasJoin(false), _id(id) // _used(false),

  {
#if defined(DEBUG)
    Application::log << "game::client created" << std::endl;
#endif
  }

  Client::Client(requestCode::SessionID id, struct sockaddr_in addr) :
    _alive(true), _updateToLive(0), _hasLeft(false),
    _hasJoin(false), // _used(false),
    _addr(addr), _id(id)
  {
#if defined(DEBUG)
    Application::log << "game::client created" << std::endl;
#endif
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

  void		Client::waitForJoin()
  {
    ARequest	*req;

    while ((req = requestPop()) != 0)
    {
      if (req->code() == requestCode::game::ALIVE)
      {
	_hasJoin = true;
#if defined(DEBUG)
	Application::log << "game::Client::waitForJoin() Client " << clientID()
		  << " on Pool " << gamePool()->poolID << " has join his game" << std::endl;
#endif // !DEBUG
      }

    }
  }

  void		Client::update(game::Game &game)
  {
    ARequest	*req;
    // bool	move = false;
    // bool	fire = false;

    while ((req = requestPop()) != 0)
    {
      // EventRequest	*ev;
      AliveRequest	*al;
      LeaveRequest	*lv;

      // if ((ev = dynamic_cast<EventRequest *>(req)) && _alive)
      // {
      // 	_updateToLive = -1;
      // 	if (ev->event() == 0 && !move)
      // 	{
      // 	  move = true;
      // 	  _player->move(ev->param());
      // 	  if (Referee::isCollision(_player, game) || !Referee::isOnScreen(_player))
      // 	  {
      // 	    _alive = false;
      // 	    game.pushRequest(new DeathRequest(_id, 0)); // STAMP !
      // 	  }
      // 	  // else
      // 	  //   game.pushRequest(new ElemRequest(requestCode::game::server::PLAYER,
      // 	  // 				     _player->_pos[0], _player->_dir, _player->_id));
      // 	}
      // 	else if (!fire)
      // 	{
      // 	  Missile *missile = _player->fire(game, false);
      // 	  game.pushMissile(missile);
      // 	  fire = true;
      // 	  // game.pushRequest(new ElemRequest(requestCode::game::server::MISSILE,
      // 	  // 				   missile->pos()[0], missile->dir(), missile->id()));
      // 	}
      // }
      if ((al = dynamic_cast<AliveRequest *>(req)))
      {
	_updateToLive = -1;
      }
      else if ((lv = dynamic_cast<LeaveRequest *>(req)))
      {
	_alive = false;
	_hasLeft = true;
      }
    }
    _updateToLive++;
    if (_updateToLive == rtype::Env::getInstance().game.updateToLive)
    {
      _alive = false;
      _hasLeft = true;
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

  requestCode::SessionID	Client::clientID() const
  {
    return (_id);
  }

  void				Client::clientID(const requestCode::SessionID id)
  {
    _id = id;
  }

  void				Client::gamePool(GamePool *pool)
  {
    _associatedPool = pool;
  }

  GamePool			*Client::gamePool() const
  {
    return (_associatedPool);
  }
}
