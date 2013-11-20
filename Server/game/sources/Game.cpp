#include <cstdlib>
#include <ctime>
#include "Referee.h"
#include "Missile.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Env.hh"
#include "IA.h"
#include "Boss.h"
#include "DeathRequest.h"
#include "ElemRequest.hh"
#include "Entity.h"
#include "Bonus.h"
#include "VictoryRequest.h"

Game::Game(std::list<game::Client *> &players)
{
  _players = players;
  incremental = 0;
  for (client_list::iterator it = _players.begin(); it != _players.end(); ++it)
    (*it)->player(new game::Player(std::vector<game::Pos> ((rand() % rtype::Env::mapSize) * rtype::Env::mapSize), UniqueId()));
  _titan = NULL;
  _clock.start();
}

Game::~Game()
{
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

  for (itia = _IA.begin(); itia != _IA.end(); itia++)
    {
      (*itia)->update();
      if (!Referee::isOnScreen(*itia))
	{
	  pushRequest(new DeathRequest((*itia)->id()));
	  delete *itia;
	  _IA.erase(itia);
	}
      else if (Referee::isCollision(*itia, *this) == true)
	{
	  (*itia)->_life--;
	  if ((*itia)->_life <= 0)
	    {
	      randBonnus(*(*itia));
	      pushRequest(new DeathRequest((*itia)->id()));
	      delete *itia;
	      _IA.erase(itia);
	    }
	}
      pushRequest(new ElemRequest((*itia)->algo()->type(),
				  (*itia)->_pos[0], (*itia)->_dir, (*itia)->_id));
    }
}

ID   &Game::UniqueId()
{
  return ++incremental;
}

void	Game::wallUpdate()
{
  std::list<Entity *>::iterator ite = _objs.begin();

  for (ite = _objs.begin(); ite != _objs.end(); ite++)
    {
      (*ite)->update();
      if (!Referee::isOnScreen(*ite))
	{
	  pushRequest(new DeathRequest((*ite)->id()));
	  delete *ite;
	  _objs.erase(ite);
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
	      _objs.erase(ite);
	    }
	}
      else
	pushRequest(new ElemRequest((*ite)->_type,
				    (*ite)->_pos[0], (*ite)->_dir, (*ite)->_id));
    }
}

void	Game::missileUpdate()
{
  std::list<Missile *>::iterator itm = _missiles.begin();

  for (itm = _missiles.begin(); itm != _missiles.end();)
    {
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
	  if (++i > (*itm)->_speed)
	    {
	      itm++;
	      break;
	    }
	}
      pushRequest(new ElemRequest((*itm)->_type,
				  (*itm)->_pos[0], (*itm)->_dir, (*itm)->_id));
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
	  break;
	  // =======
	  // 		(*itb)->update();
	  // 		if (!Referee::isOnScreen(*itb) || Referee::isCollision(*itb, *this))
	  // 		{
	  // 		    pushRequest(new DeathRequest((*itb)->id()));
	  // 			delete *itb;
	  // 			itb = _bonus.erase(itb);
	  // 			break;
	  // 		}
	  // 		pushRequest(new ElemRequest((*itb)->_type,
	  // 			(*itb)->_pos[0], (*itb)->_dir, (*itb)->_id));
	  // >>>>>>> 5e0ea9ea588e259eb202a363faa109e7e03b50b9
	}
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
	  pushRequest(new VictoryRequest());
	  delete _titan;
	}
      if (Referee::isCollision(_titan, *this))
	{
	  _titan->_life--;
	  if (_titan->_life <= 0)
	    {
	      pushRequest(new DeathRequest(_titan->id()));
	      pushRequest(new VictoryRequest());
	      delete _titan;
	    }
	}
      pushRequest(new ElemRequest(_titan->algo()->type(),
				  _titan->_pos[0], _titan->_dir, _titan->_id));
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

void	Game::playerUpdate()
{
  std::list<game::Client *>::iterator itm = _players.begin();

  for (itm = _players.begin(); itm != _players.end();)
    {
      (*itm)->update(*this);
      if (!Referee::isOnScreen((*itm)->_player) || Referee::isCollision((*itm)->_player, *this))
	{
	  if ((*itm)->_player->_extraLife == true)
	    {
	      (*itm)->_player->_extraLife = false;
	      itm++;
	    }
	  else
	    {
	      itm = _players.erase(itm);
	      break;
	    }
	}
      else
	itm++;
    }
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
  if (_IA.size() < rtype::Env::maxIA)
    {
      if (_IA.size() < rtype::Env::minIA || rand() % rtype::Env::popIAmax < rtype::Env::popIArange)
	{

	  /*
	    Ia *new_ia;

	    new_ia = BotLoader::getIA();
	    with pos = rand() % Entity::SIZE + Entity::SIZE - 1;
	    id = UniqueId();

	    _IA.push_back(new_ia);
	    pushRequest(new ElemRequest(new_ia->_type,
	    new_ia->_pos, new_ia->_dir, new_ia->_id));
	  */
	}
    }
}

Game::client_list	&Game::clients()
{
  return (_players);
}

void	Game::pushBoss()
{
  /*
    _titan = new Boss(UniqueId(), BotLoader::getBoss());
    pushRequest(new ElemRequest(_titan->_algo->type(),
    _titan->pos()[0], _titan->dir(), _titan->id()));
  */
}

void	Game::update()
{
  playerUpdate();
  iaUpdate();
  wallUpdate();
  missileUpdate();
  bonusUpdate();
  _clock.update();
  if (rtype::Env::BOSS_DELAY <= _clock.getTotalElapsedTime())
    pushBoss();
  popIA();

  DispatchRequest();
}
