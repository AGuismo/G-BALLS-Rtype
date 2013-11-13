#include "Referee.h"
#include "Missile.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Env.hh"

Game::Game(std::list<game::Player *> &players)
{
  _players = players;
  _titan = NULL;
}

Game::~Game()
{

}

void	Game::iaUpdate()
{
  std::list<Ia *>::iterator itia = _IA.begin();

  for (itia = _IA.begin(); itia != _IA.end(); itia++)
    {
      (*itia)->update();
      if (!Referee::isOnScreen(*itia))
	{
	  delete *itia;
	  _IA.erase(itia);
	}
      else if (Referee::isCollision(*itia, *this) == true)
	{
	  (*itia)->_life--;
	  if ((*itia)->_life <= 0)
	    {
	      delete *itia;
	      _IA.erase(itia);
	    }
	}
    }
}

void	Game::wallUpdate()
{
  std::list<Entity *>::iterator ite = _objs.begin();

  for (ite = _objs.begin(); ite != _objs.end(); ite++)
    {
      (*ite)->update();
      if (!Referee::isOnScreen(*ite))
	{
	  delete *ite;
	  _objs.erase(ite);
	}
      else if (Referee::isCollision(*ite, *this) == true)
	{
	  if ((*ite)->_type == DESTRUCTIBLEWALL)
	    (*ite)->_life--;
	  if ((*ite)->_life <= 0)
	    {
	      delete *ite;
	      _objs.erase(ite);
	    }
	}
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
    }
}

void	Game::bossUpdate()
{
  if (_titan)
    {
      _titan->update();
      if (!Referee::isOnScreen(_titan))
	{
	  delete	_titan;
	}
      if (Referee::isCollision(_titan, *this))
	{

	}
    }
}

void	Game::update()
{
  iaUpdate();
  wallUpdate();
  missileUpdate();

  _timer->tv_usec = rtype::Env::gameDelay;
  _timer->tv_sec = 0;
}
