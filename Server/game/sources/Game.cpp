#include	<cstdlib>
#include	<ctime>
#include	<vector>
#include	<algorithm>
#include	"Game.hh"
#include	"LoaderManager.hh"
#include	"Referee.h"
#include	"Missile.h"
#include	"Entity.h"
#include	"Player.h"
#include	"Env.hh"
#include	"IA.h"
#include	"Boss.h"
#include	"BaseBoss.h"
#include	"DeathRequest.h"
#include	"ElemRequest.hh"
#include	"Entity.h"
#include	"Bonus.h"
#include	"VictoryRequest.h"
#include	"LooseRequest.h"
#include	"NextStage.hh"
#include	"BaseIA.h"
#include	"Protocol.hpp"
#include	"GamePool.hh"
#include	"GameManager.hh"
#include	"Application.hh" // Log purpose

namespace game
{

  ////////////////////////////
  // Constructor/Destructor //
  ////////////////////////////

  Game::Game(std::list<game::Client *> &players)
  {
    _parent = 0;
    _clients = players;
    _incremental = 0;
    _clock.start();
    _timer.tv_sec = 0;
    _attempsClientConfirmation = rtype::Env::getInstance().game.updateToLive;
    _timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
    _status = WAITING_PLAYER;
    _success = false;
#if defined(DEBUG)
    Application::log << "Game::Game(): " << "Bienvenue dans la faille de l'invocateur" << std::endl;
#endif
  }

  Game::~Game()
  {
    while (!_IA.empty())
    {
      delete _IA.front();
      _IA.pop_front();
    }
    while (!_objs.empty())
    {
      delete _objs.front();
      _objs.pop_front();
    }
    while (!_missiles.empty())
    {
      delete _missiles.front();
      _missiles.pop_front();
    }
    while (!_bonus.empty())
    {
      delete _bonus.front();
      _bonus.pop_front();
    }
    while (!_titans.empty())
    {
      delete _titans.front();
      _titans.pop_front();
    }
    // while (!_clients.empty())
    // {
    //   delete _clients.front()->player();
    //   _clients.pop_front();
    // }
#if defined(DEBUG)
    Application::log << "A Game has just finished" << std::endl;
#endif
  }


  //////////////////
  // Game updates //
  //////////////////

  void	Game::randBonnus(Entity &a)
  {
    int dice_roll = rand() % 6;
    if (dice_roll == 5)
    {
      if (!(dice_roll = rand() % 2))
      {
	_bonus.push_back(new game::ExtraLife(game::WEST, a.pos()[0], UniqueId()));
	// pushRequest(new ElemRequest((_bonus.back())->type(),
	// 			    (_bonus.back())->pos()[0], (_bonus.back())->dir(),
	// 			    (_bonus.back())->id()));
	/*CAREFUL HERE*/
      }
      else
      {
	_bonus.push_back(new game::Pow(game::WEST, a.pos()[0], UniqueId()));
	// pushRequest(new ElemRequest((_bonus.back())->type(),
	// 			    (_bonus.back())->pos()[0], (_bonus.back())->dir(),
	// 			    (_bonus.back())->id()));
      }
    }
  }

  void	Game::iaUpdate()
  {
    std::list<Ia *>::iterator itia = _IA.begin();

    for (itia = _IA.begin(); itia != _IA.end(); )
    {
      bool						flag = false;

      (*itia)->update(*this);
      if (!Referee::isOnScreen(*itia))
      {
	pushRequest(new DeathRequest((*itia)->id()));
	delete *itia;
	itia = _IA.erase(itia);
	flag = true;
      }
      else if (Referee::isCollision(*itia, *this) == true)
      {
	(*itia)->_life--;
	if ((*itia)->_life <= 0)
	{
	  randBonnus(*(*itia));
	  pushRequest(new DeathRequest((*itia)->id()));
	  delete *itia;
	  itia = _IA.erase(itia);
	  flag = true;
	}
      }
      if (flag == false)
      {
	// pushRequest(new ElemRequest((*itia)->algo()->type(),
	// 			    (*itia)->_pos[0], (*itia)->_dir, (*itia)->_id));
	itia++;
      }
    }
  }

  void	Game::wallUpdate()
  {
    std::list<Entity *>::iterator ite = _objs.begin();

    for (ite = _objs.begin(); ite != _objs.end(); )
    {
      bool			flag = false;

      (*ite)->update();
      if (!Referee::isOnScreen(*ite))
      {
	pushRequest(new DeathRequest((*ite)->id()));
	delete *ite;
	ite = _objs.erase(ite);
	flag = true;
      }
      else if (Referee::isCollision(*ite, *this) == true)
      {
	if ((*ite)->_type == requestCode::game::server::DESTRUCTIBLE_WALL)
	  (*ite)->_life--;
	if ((*ite)->_life <= 0)
	{
	  randBonnus(*(*ite));
	  pushRequest(new DeathRequest((*ite)->id()));
	  delete *ite;
	  ite = _objs.erase(ite);
	  flag = true;
	}
      }
      else
	// pushRequest(new ElemRequest((*ite)->_type,
	// 			    (*ite)->_pos[0], (*ite)->_dir, (*ite)->_id));
	if (flag == false)
	  ite++;
    }
  }

  void	Game::missileUpdate()
  {
    std::list<Missile *>::iterator itm;

    for (itm = _missiles.begin(); itm != _missiles.end();)
    {
      bool						flag = true;

      for (unsigned int i = 0;;)
      {
	(*itm)->update();
	if (!Referee::isOnScreen(*itm) || Referee::isCollision(*itm, *this))
	{
	  pushRequest(new DeathRequest((*itm)->id()));
	  delete *itm;
	  itm = _missiles.erase(itm);
	  flag = false;
	  break;
	}
	if (++i >= (*itm)->_speed)
	{
	  flag = true;
	  break;
	}
      }
      if (flag == true)
      {
	// pushRequest(new ElemRequest((*itm)->_typeMissile,
	// 			    (*itm)->_pos[0], (*itm)->_dir, (*itm)->_id));
	itm++;
      }
    }
  }

  void	Game::bonusUpdate()
  {
    std::list<game::ABonus *>::iterator itb = _bonus.begin();

    for (itb = _bonus.begin(); itb != _bonus.end();)
    {
      (*itb)->update();
      if (!Referee::isOnScreen(*itb) || Referee::isCollision(*itb, *this))
      {
	pushRequest(new DeathRequest((*itb)->id()));
	delete *itb;
	itb = _bonus.erase(itb);
      }
      else
      {
	// pushRequest(new ElemRequest((*itb)->_type,
	// 			    (*itb)->_pos[0], (*itb)->_dir, (*itb)->_id));
	itb++;
      }
    }
  }

  void	Game::bossUpdate()
  {
    if (_titan)
    {
      _titan->update(*this);
      if (!Referee::isOnScreen(_titan))
      {
	pushRequest(new DeathRequest(_titan->id()));
	if (_titans.empty())
	  _status = FINISHED;
	// pushRequest(new VictoryRequest());
	else
	{
	  pushRequest(new NextStageRequest());
	  _clock.restart();
	}
	delete _titan;
      }
      if (Referee::isCollision(_titan, *this))
      {
	_titan->_life--;
	if (_titan->_life <= 0)
	{
	  pushRequest(new DeathRequest(_titan->id()));
	  if (_titans.empty())
	    _status = FINISHED;
	  else
	  {
	    pushRequest(new NextStageRequest());
	    _clock.restart();
	  }
	  delete _titan;
	}
      }
      // pushRequest(new ElemRequest(_titan->algo()->type(),
      // 				  _titan->_pos[0], _titan->_dir, _titan->_id));
    }
  }

  void	Game::pushMissile(Missile *missile)
  {
    _missiles.push_back(missile);
  }

  void	Game::pushRequest(ARequest *req)
  {
    _toSend.requestPush(req);
  }

  bool	Game::playerUpdate()
  {
    std::list<game::Client *>::iterator itm = _clients.begin();

    for (itm = _clients.begin(); itm != _clients.end(); )
    {
      (*itm)->update(*this);
      if ((*itm)->hasLeft())
      {
	// delete (*itm)->player();
	itm = _clients.erase(itm);
	return true;
      }
      else
	itm++;
    }
    return false;
  }

  void	Game::popIA()
  {
    if (_IA.size() < rtype::Env::getInstance().game.maxIA)
    {
      if (_IA.size() < rtype::Env::getInstance().game.minIA || rand() % rtype::Env::getInstance().game.popIAmax < rtype::Env::getInstance().game.popIArange)
      {
	Ia *new_ia;
	AIaAlgo	*algo = 0;
	// AIaAlgo	*algo = botLoader::Manager::getInstance().getSimpleBydos();

	if (algo != 0)
	  new_ia = new Ia(UniqueId(), algo);
	else
	  new_ia = new Ia(UniqueId(), new BaseIA());

	_IA.push_back(new_ia);
	// pushRequest(new ElemRequest(new_ia->algo()->type(),
	// 			    new_ia->_pos[0], new_ia->_dir, new_ia->_id));

      }
    }
  }

  void	Game::popWall()
  {
    if (_objs.size() < rtype::Env::getInstance().game.maxWall)
    {
      if (_objs.size() < rtype::Env::getInstance().game.minWall ||
	  rand() % rtype::Env::getInstance().game.popRangeMaxWall < rtype::Env::getInstance().game.popRangeMinWall)
      {
	Entity *wall;

	if (rand() % rtype::Env::getInstance().game.chanceToBreakableMax < rtype::Env::getInstance().game.chanceToBreakableMin)
	{
	  game::Pos p;
	  while ((p = 15 * (rand() % rtype::Env::getInstance().game.mapSize)) != 0)
	    ;
	  wall = new Entity(requestCode::game::server::DESTRUCTIBLE_WALL, std::vector<game::Pos>(1, p), 3, 6, UniqueId());
	}
	else
	{
	  game::Pos p = rand() % 2 == 1 ? rtype::Env::getInstance().game.mapSize - 1 :
	    rtype::Env::getInstance().game.mapSize * rtype::Env::getInstance().game.mapSize -1;
	  wall = new Entity(requestCode::game::server::INDESTRUCTIBLE_WALL, std::vector<game::Pos>(1, p), -1, 6, UniqueId());
	}
	_objs.push_back(wall);
	// pushRequest(new ElemRequest(wall->type(),
	// 			    wall->_pos[0], wall->_dir, wall->_id));

      }
    }
  }


  /////////////////////////////////////////
  // General updates, messages to parents//
  /////////////////////////////////////////

  void	Game::updateGame()
  {
#if defined(DEBUG)
    Application::log << "Game::updateGame() - " << this << ": GAME UPDATE" << std::endl;
#endif
    playerUpdate();
    iaUpdate();
    wallUpdate();
    missileUpdate();
    bonusUpdate();
    _clock.update();
    if (rtype::Env::BOSS_DELAY <= _clock.getTotalElapsedTime() && !_titan)
    {
      if (!_titans.empty())
      {
	_titan = _titans.front();
	// pushRequest(new ElemRequest(_titan->algo()->type(),
	// 			    _titan->pos()[0], _titan->dir(), _titan->id()));
	_titans.pop_front();
      }
      else
      {
	_status = FINISHED;
	_success = true;
	// pushRequest(new VictoryRequest()); // TODO
      }
    }
    popIA();
    popWall();
    if (Referee::asAlivePlayers(*this) == false)
    {
      _status = FINISHED;
      _success = false;
      // pushRequest(new LooseRequest()); // TODO
    }
    sendUpdates();
  }


  void	Game::cancelGame()
  {
    _parent->cancelGame(this);
    // Envoyer a tous les clients un Game::Cancel (TCP)
  }

  void	Game::endGame()
  {
    _parent->endGame(this);
    // Envoyer a tous les clients un Game::Victory/Loose (TCP)
  }

  void		Game::prepareGame()
  {
    game::Type t = requestCode::game::server::PLAYER1;

    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
      int	pos;

      pos = (rand() % rtype::Env::getInstance().game.mapSize);
      pos *= rtype::Env::getInstance().game.mapSize;
      (*it)->player(new game::Player(std::vector<game::Pos>(1, pos), UniqueId(), t));
      t++;
#if defined(DEBUG)
      Application::log << "game::Game::prepareGame() - Game " << this
		<< ", create player " << (*it)->player()->id()
		<< " at pos (" << pos % rtype::Env::getInstance().game.mapSize
		<< ", " << pos / rtype::Env::getInstance().game.mapSize << ")" << std::endl;
#endif // !DEBUG
    }
    _titan = NULL;
    for (int i = 0; i < rtype::Env::getInstance().game.maxBoss; ++i)
    {
      // AIaAlgo	*algo = botLoader::Manager::getInstance().getBossBydos();
      AIaAlgo	*algo = 0;

      if (algo != 0)
	_titans.push_back(new Boss(UniqueId(), algo));
      else
	_titans.push_back(new Boss(UniqueId(), new BaseBoss()));
    }
  }

  void		Game::waitingForPlayers()
  {
    bool	ready = true;

    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
      (*it)->waitForJoin();
      if (!(*it)->hasJoin())
	ready = false;
    }
    if (ready)
    {
      prepareGame();
      _status = IN_GAME;
      return ;
    }
    if (--_attempsClientConfirmation == 0)
    {
      _status = CANCELED;
#if defined(DEBUG)
      Application::log << "Game::update() - Game " << this << " Cancelled" << std::endl;
    }
    else
    {
      Application::log << "Game::update() - Game " << this << ", " << _attempsClientConfirmation
		<< " before cancellation" << std::endl;
#endif // !DEBUG
    }
  }

  bool	Game::update()
  {
    if (_status == WAITING_PLAYER)
    {
      waitingForPlayers();
    }
    else if (_status == IN_GAME)
      updateGame();

    if (_status == FINISHED)
    {
      endGame();
#if defined(DEBUG)
      Application::log << "Game::update() - Game " << this << " has just finished" << std::endl;
#endif // !DEBUG
    }
    else if (_status == CANCELED)
    {
      cancelGame();
#if defined(DEBUG)
      Application::log << "Game::update() - Game " << this << " was canceled" << std::endl;
#endif // !DEBUG
      return (false);
    }
    _timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
    return (true);
  }

  //////////////////////////
  // Send info to players //
  //////////////////////////
  void	Game::send(const ARequest &req)
  {
    for (client_list::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
      std::vector<Protocol::Byte>	buf;
      char				data[512];

      buf = Protocol::product(req);
      std::copy(buf.begin(), buf.end(), data);
      _parent->parent()->server().directWrite(data, buf.size(), (*it)->getAddr());
    }
  }

  void	Game::sendUpdates()
  {
    while (!_toSend.empty())
    {
      ARequest *req = _toSend.requestPop();

      send(*req);
    }

    for (client_list::const_iterator it = _clients.begin(); it != _clients.end(); it++)
    {
      const Player	*p = (*it)->player();

      send(ElemRequest(requestCode::game::server::PLAYER, p->_pos[0], p->_dir, p->_id));
    }

    for (ia_list::const_iterator it = _IA.begin(); it != _IA.end(); it++)
      send(ElemRequest((*it)->algo()->type(), (*it)->_pos[0], (*it)->_dir, (*it)->_id));

    for (entity_list::const_iterator it = _objs.begin(); it != _objs.end(); it++)
      send(ElemRequest((*it)->type(), (*it)->_pos[0], (*it)->_dir, (*it)->_id));

    for (missile_list::const_iterator it = _missiles.begin(); it != _missiles.end(); it++)
      send(ElemRequest((*it)->type(), (*it)->_pos[0], (*it)->_dir, (*it)->_id));

    for (bonus_list::const_iterator it = _bonus.begin(); it != _bonus.end(); it++)
      send(ElemRequest((*it)->type(), (*it)->_pos[0], (*it)->_dir, (*it)->_id));

    if (_titan != 0)
      send(ElemRequest(_titan->algo()->type(), _titan->_pos[0], _titan->_dir, _titan->_id));
  }

  /////////////
  // Get/Set //
  /////////////


  Game::client_list	&Game::clients()
  {
    return (_clients);
  }

  const Game::client_list	&Game::clients() const
  {
    return (_clients);
  }

  bool			Game::success() const
  {
    return (_success);
  }

  void			Game::timer(struct timeval t)
  {
    _timer = t;
  }

  struct timeval	&Game::timer()
  {
    return _timer;
  }

  const struct timeval	&Game::timer() const
  {
    return _timer;
  }

  ID			&Game::UniqueId()
  {
    return ++_incremental;
  }

  void			Game::parent(GamePool *parent)
  {
    _parent = parent;
  }

  GamePool		*Game::gamePool() const
  {
    return (_parent);
  }

  Game::Status		Game::status() const
  {
    return (_status);
  }

}


//////////////
// Old Code //
//////////////

//   bool	Game::update()
//   {
// #if defined(DEBUG)
//     Application::log << "GAME UPDATE" << std::endl;
// #endif
//     bool asleftplayer = playerUpdate();
//     if (_isFinished == false)
//     {
//       iaUpdate();
//       wallUpdate();
//       missileUpdate();
//       bonusUpdate();
//       _clock.update();
//       if (rtype::Env::BOSS_DELAY <= _clock.getTotalElapsedTime() && !_titan)
//       {
// 	if (!_titans.empty())
// 	{
// 	  _titan = _titans.front();
// 	  pushRequest(new ElemRequest(_titan->algo()->type(),
// 				      _titan->pos()[0], _titan->dir(), _titan->id()));
// 	  _titans.pop_front();
// 	}
// 	else
// 	{
// 	  _isFinished = true;
// 	  pushRequest(new VictoryRequest());
// 	}
//       }
//       popIA();
//       popWall();
//       if (Referee::asAlivePlayers(*this) == false)
//       {
// 	pushRequest(new LooseRequest());
// 	_isFinished = true;
//       }
//     }
//     DispatchRequest();
//     _timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
//     return asleftplayer;
//   }
