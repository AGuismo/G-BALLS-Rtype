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
  for (client_list::iterator it = _players.begin(); it != _players.end(); ++it)
	  (*it)->player(new game::Player(std::vector<game::Pos>(1, (rand() % rtype::Env::getInstance().game.mapSize) *
																rtype::Env::getInstance().game.mapSize), UniqueId()));
  _titan = NULL;
  for (int i = 0; i < rtype::Env::getInstance().game.maxBoss; ++i)
  {
      if (botLoader::Manager::getInstance().getBossBydos())
	  _titans.push_back(new Boss(UniqueId(), botLoader::Manager::getInstance().getBossBydos()));
      else
	  _titans.push_back(new Boss(UniqueId(), new BaseBoss()));
  }
  _clock.start();
  _timer.tv_sec = 0;
  _launchGameTime = 8;
  _timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
  std::cout << "Game::Game(): " << "Bienvenue dans la faille de l'invocateur" << std::endl;
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
    std::cout << "A Game has just finished" << std::endl;
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
	  pushRequest(new ElemRequest((*_bonus.end())->type(),
				      (*_bonus.end())->pos()[0], (*_bonus.end())->dir(),
				      (*_bonus.end())->id()));
	}
      else
	{
	  _bonus.push_back(new game::Pow(game::WEST, a.pos()[0], UniqueId()));
	  pushRequest(new ElemRequest((*_bonus.end())->type(),
				      (*_bonus.end())->pos()[0], (*_bonus.end())->dir(),
				      (*_bonus.end())->id()));
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
      pushRequest(new ElemRequest((*itia)->algo()->type(),
				  (*itia)->_pos[0], (*itia)->_dir, (*itia)->_id));
	  if (flag == false)
		  itia++;
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
	  if ((*ite)->_type == game::DESTRUCTIBLEWALL)
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
	  bool						flag = false;

      for (unsigned int i = 0;;)
		{
		  (*itm)->update();
		  if (!Referee::isOnScreen(*itm) || Referee::isCollision(*itm, *this))
			{
			  pushRequest(new DeathRequest((*itm)->id()));
			  delete *itm;
			  itm = _missiles.erase(itm);
			  break;
			}
		  if (++i >= (*itm)->_speed)
			{
			  flag = true;
			  break;
			}
		}
	  pushRequest(new ElemRequest((*itm)->_type,
		  (*itm)->_pos[0], (*itm)->_dir, (*itm)->_id));
	  if (flag == true)
		  itm++;
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
		  itb++;
      pushRequest(new ElemRequest((*itb)->_type,
				  (*itb)->_pos[0], (*itb)->_dir, (*itb)->_id));
    }
}

void	Game::bossUpdate()
{
  if (_titan)
    {
      _titan->update();
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

			//new_ia = BotLoader::getIA();
			//with pos = rand() % Entity::SIZE + Entity::SIZE - 1;
			//id = UniqueId();
			if (botLoader::Manager::getInstance().getSimpleBydos())
			    new_ia = new Ia(UniqueId(), botLoader::Manager::getInstance().getSimpleBydos());
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
				wall = new Entity(UniqueId(), std::vector<game::Pos>(1, p), 3, 6, UniqueId());
			}
			else
			{
				game::Pos p = rand() % 2 == 1 ? rtype::Env::getInstance().game.mapSize - 1 :
												rtype::Env::getInstance().game.mapSize * rtype::Env::getInstance().game.mapSize -1;
				wall = new Entity(UniqueId(), std::vector<game::Pos>(1, p), -1, 6, UniqueId());
			}
			_objs.push_back(wall);
			pushRequest(new ElemRequest(wall->type(),
				wall->_pos[0], wall->_dir, wall->_id));

		}
	}
}

bool	Game::update()
{
	std::cout << "GAME UPDATE" << std::endl;
	bool asleftplayer = playerUpdate();
	iaUpdate();
	wallUpdate();
	missileUpdate();
	bonusUpdate();
	_clock.update();
	if (rtype::Env::BOSS_DELAY <= _clock.getTotalElapsedTime()&& !_titan)
	{
	    if (!_titans.empty())
	    {
		_titan = _titans.front();
		pushRequest(new ElemRequest(_titan->algo()->type(),
			    _titan->pos()[0], _titan->dir(), _titan->id()));
		_titans.pop_front();
	    }
	    else
		pushRequest(new VictoryRequest());
	}
	popIA();
	popWall();
	if (Referee::asAlivePlayers(*this) == false)
		pushRequest(new LooseRequest());
	DispatchRequest();
	_timer.tv_usec = rtype::Env::getInstance().game.gameDelay;
	return asleftplayer;
}
