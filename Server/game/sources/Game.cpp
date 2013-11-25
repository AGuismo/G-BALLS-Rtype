#include <cstdlib>
#include <ctime>
#include <vector>
#include "Game.h"
#include "LoaderManager.hh"
#include "Referee.h"
#include "Missile.h"
#include "Entity.h"
#include "Player.h"
#include "Env.hh"
#include "IA.h"
#include "Boss.h"
#include "BaseBoss.h"
#include "DeathRequest.h"
#include "ElemRequest.hh"
#include "Entity.h"
#include "Bonus.h"
#include "VictoryRequest.h"
#include "LooseRequest.h"
#include "NextStage.hh"
#include "BaseIA.h"

Game::Game(std::list<game::Client *> &players)
{
  _players = players;
  incremental = 0;
  game::Type t = requestCode::game::server::PLAYER1;
  for (client_list::iterator it = _players.begin(); it != _players.end(); ++it)
  {
	  (*it)->player(new game::Player(std::vector<game::Pos>(1, (rand() % rtype::Env::getInstance().game.mapSize) *
		  rtype::Env::getInstance().game.mapSize), UniqueId(), t));
	  pushRequest(new ElemRequest(t, (*it)->player()->pos()[0], (*it)->player()->dir(), (*it)->player()->id()));
	  t++;
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
  _clock.start();
  _timer.tv_sec = 0;
  _launchGameTime = 8;
  _timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
  _isFinished = false;
#if defined(DEBUG)
  std::cout << "Game::Game(): " << "Bienvenue dans la faille de l'invocateur" << std::endl;
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
    while (!_players.empty())
    {
	delete _players.front()->player();
	_players.pop_front();
    }
    while (!_titans.empty())
    {
	delete _titans.front();
	_titans.pop_front();
    }
#if defined(DEBUG)
    std::cout << "A Game has just finished" << std::endl;
#endif
}

void	Game::randBonnus(Entity &a)
{
  srand((unsigned int)(time(NULL)));
  int dice_roll = rand() % 6;
  if (dice_roll == 5)
    {
      if (!(dice_roll = rand() % 2))
	{
	  _bonus.push_back(new game::ExtraLife(game::WEST, a.pos()[0], UniqueId()));
	  pushRequest(new ElemRequest((_bonus.back())->type(),
				      (_bonus.back())->pos()[0], (_bonus.back())->dir(),
				      (_bonus.back())->id()));
	  /*CAREFUL HERE*/
	}
      else
	{
	  _bonus.push_back(new game::Pow(game::WEST, a.pos()[0], UniqueId()));
	  pushRequest(new ElemRequest((_bonus.back())->type(),
		  (_bonus.back())->pos()[0], (_bonus.back())->dir(),
		  (_bonus.back())->id()));
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
		  pushRequest(new ElemRequest((*itia)->algo()->type(),
			  (*itia)->_pos[0], (*itia)->_dir, (*itia)->_id));
		  itia++;
	  }
	}
}

ID   &Game::UniqueId()
{
  return ++incremental;
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
		pushRequest(new ElemRequest((*ite)->_type,
				      (*ite)->_pos[0], (*ite)->_dir, (*ite)->_id));
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
		  pushRequest(new ElemRequest((*itm)->_typeMissile,
			  (*itm)->_pos[0], (*itm)->_dir, (*itm)->_id));
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
		  pushRequest(new ElemRequest((*itb)->_type,
			  (*itb)->_pos[0], (*itb)->_dir, (*itb)->_id));
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
	      pushRequest(new VictoryRequest());
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
		  pushRequest(new VictoryRequest());
	      else
	      {
		  pushRequest(new NextStageRequest());
		  _clock.restart();
	      }
	      delete _titan;
	    }
	}
      pushRequest(new ElemRequest(_titan->algo()->type(),
				  _titan->_pos[0], _titan->_dir, _titan->_id));
    }
}

void	Game::timer(struct timeval t)
{
	_timer = t;
}

struct timeval &Game::timer()
{
	return _timer;
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
  std::list<game::Client *>::iterator itm = _players.begin();

  for (itm = _players.begin(); itm != _players.end(); )
    {
      (*itm)->update(*this);
	  if ((*itm)->hasLeft())
	  {
		delete (*itm)->player();
		itm = _players.erase(itm);
		return true;
	  }
	  else
		  itm++;
    }
  return false;
}

void	Game::DispatchRequest()
{
  while (!_toSend.empty())
    {
      ARequest *req = _toSend.requestPop();

      for (std::list<game::Client *>::iterator it = _players.begin();
	   it != _players.end();
	   it++)
	{
	  (*it)->requestPush(req);
	}

    }
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
			pushRequest(new ElemRequest(new_ia->algo()->type(),
			new_ia->_pos[0], new_ia->_dir, new_ia->_id));

		}
    }
}

Game::client_list	&Game::clients()
{
  return (_players);
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
			pushRequest(new ElemRequest(wall->type(),
				wall->_pos[0], wall->_dir, wall->_id));

		}
	}
}

bool	Game::update()
{
#if defined(DEBUG)
	std::cout << "GAME UPDATE" << std::endl;
#endif
	bool asleftplayer = playerUpdate();
	if (_isFinished == false)
	{
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
				pushRequest(new ElemRequest(_titan->algo()->type(),
					_titan->pos()[0], _titan->dir(), _titan->id()));
				_titans.pop_front();
			}
			else
			{
				_isFinished = true;
				pushRequest(new VictoryRequest());
			}
		}
		popIA();
		popWall();
		if (Referee::asAlivePlayers(*this) == false)
		{
			pushRequest(new LooseRequest());
			_isFinished = true;
		}
	}
	DispatchRequest();
	_timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
	return asleftplayer;
}
