// LibProtocol
#include	"AliveRequest.hh"
#include	"ElemRequest.hh"
#include	"DeathRequest.hh"
#include	"LeaveRequest.hh"

// LibReferee
#include	"Player.hh"
#include	"Missile.hh"
#include	"MainReferee.hh"

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
    _requestCallback[requestCode::game::LEAVE] = &Client::request_leave;
    _requestCallback[requestCode::game::ALIVE] = &Client::request_alive;
    _requestCallback[requestCode::game::ELEM] = &Client::request_elem;

  }

  Client::Client(requestCode::SessionID id, struct sockaddr_in addr) :
    _alive(true), _updateToLive(0), _hasLeft(false),
    _hasJoin(false), // _used(false),
    _addr(addr), _id(id)
  {
#if defined(DEBUG)
    Application::log << "game::client created" << std::endl;
#endif

    _requestCallback[requestCode::game::LEAVE] = &Client::request_leave;
    _requestCallback[requestCode::game::ALIVE] = &Client::request_alive;
    _requestCallback[requestCode::game::ELEM] = &Client::request_elem;
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

  void		Client::update(MainReferee &game)
  {
    ARequest	*req;
    // bool	move = false;
    // bool	fire = false;

    std::cerr << "Client::update(): " << _updateToLive << std::endl;
    _updateToLive++;
    while ((req = requestPop()) != 0)
    {
      request_callback_map_type::iterator	found = _requestCallback.find(req->code());

      if (found != _requestCallback.end())
	(this->*(found->second))(*req, game);

      // EventRequest	*ev;
      // AliveRequest	*al;
      // LeaveRequest	*lv;
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
    }
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

  // Request Callbacks

  void		Client::request_alive(const ARequest &req, MainReferee &referee)
  {
    _updateToLive = 0;
    (void)referee;
  }

  void		Client::request_leave(const ARequest &req, MainReferee &referee)
  {
    _alive = false;
    _hasLeft = true;
    // TODO: referee.hasLeft(playerID);
  }

  void		Client::request_elem(const ARequest &req, MainReferee &referee)
  {
    const ElemRequest	&elem = dynamic_cast<const ElemRequest &>(req);

    if (elem.entity()->getType().desc.maj == Entity::PLAYER)
      referee.acceptPlayerPosition(dynamic_cast<const Player &>(*elem.entity()), elem.Stamp());
    else if (elem.entity()->getType().desc.maj == Entity::MISSILE)
      referee.acceptFire(dynamic_cast<const Missile &>(*elem.entity()), elem.Stamp());
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
