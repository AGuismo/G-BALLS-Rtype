#include "Referee.h"
#include "Game.h"

Referee::Referee()
{

}

Referee::~Referee()
{

}

void	Referee::update(Game &game)
{
  (void)game;
}

void	Referee::getIA()
{

}

void	Referee::getBoss()
{

}

bool	Referee::isOnScreen(const Entity *a)
{
	if ((_pos < 0 || _pos > 255) ||
		(a->posX() + 1 != a->prevX() ||
		a->posX() - 1 != a->prevX()))
		return false;
	return true;
}

bool	Referee::sameCase(const Entity *a, const Entity *b)
{
  if (a->posX() <= b->posX() &&
      a->posX() + a->_length >= b->posX() &&
      a->_posy <= b->_posy &&
      a->_posy + a->_height >= b->_posy)
    return true;
  if (a->posX() <= b->posX() + b->_length &&
      a->posX() + a->_length >= b->posX() + b->_length &&
      a->_posy <= b->_posy &&
      a->_posy + a->_height >= b->_posy)
    return true;
  if (a->posX() <= b->posX() &&
      a->posX() + a->_length >= b->posX() &&
      a->_posy <= b->_posy + b->_height &&
      a->_posy + a->_height >= b->_posy + b->_height)
    return true;
  if (a->posX() <= b->posX() + b->_length &&
      a->posX() + a->_length >= b->posX() + b->_length &&
      a->_posy <= b->_posy + b->_height &&
      a->_posy + a->_height >= b->_posy + b->_height)
    return true;
  return false;
}


bool	Referee::playerCollision(Entity *a, Game &game)
{
  std::list<Player *>::iterator itp = game._players.begin();

  for (; itp != game._players.end(); itp++)
    {
      if (a->_type != PLAYER && a->_type != MISSILE &&
	  sameCase(a, *itp) == true)
	{
	  if ((*itp)->_extraLife == true)
	    (*itp)->_extraLife = false;
	  else
	    {
	      delete *itp;
	      game._players.erase(itp);
	    }
	  return true;
	}
      else if (a->_type == MISSILE &&
	       sameCase(a, *itp) == true)
	{
	  if (dynamic_cast<Missile *>(a)->getLauncher()->_type != PLAYER)
	    {
	      delete *itp;
	      game._players.erase(itp);
	      return true;
	    }
	}
    }
  return false;
}

static bool	iaCollision(Entity *a, Game &game)
{
	std::list<Ia *>::iterator itia = game._IA.begin();

  for (; itia != game._IA.end(); itia++)
    {
      if (a->_type != IA && a->_type != MISSILE &&
	  sameCase(a, *itia) == true)
	{
	  (*itia)->_life--;
	  if ((*itia)->_life <= 0)
	    {
	      delete *itia;
	      game._IA.erase(itia);
	    }
	  return true;
	}
      else if (a->_type == MISSILE &&
	       sameCase(a, *itia) == true)
	{
	  if (dynamic_cast<Missile *>(a)->getLauncher()->_type != IA)
	    {
	      (*itia)->_life--;
	      if ((*itia)->_life <= 0)
		{
		  delete *itia;
		  game._IA.erase(itia);
		}
	      return true;
	    }
	}
    }
	return false;
}
static bool	wallCollision(Entity *a, Game &game)
{
  std::list<Entity *>::iterator ite = game._objs.begin();

  for (; ite != game._objs.end(); ite++)
    {
      if (a->_type != WALL && a->_type != DESTRUCTIBLEWALL &&
	  sameCase(a, *ite) == true)
	{
	  if ((*ite)->_type != WALL)
	    {
	      (*ite)->_life--;
	      if ((*ite)->_life <= 0)
		{
		  delete *ite;
		  game._objs.erase(ite);
		}
	    }
	  return true;
	}
    }
	return false;
}

static bool	missileCollision(Entity *a, Game &game)
{
  std::list<Missile *>::iterator itm = game._missiles.begin();

  for (; itm != game._missiles.end(); itm++)
    {
      if (a->_type != MISSILE &&
	  sameCase(a, *itm) == true)
	{
	  delete *itm;
	  game._missiles.erase(itm);
	  return true;
	}
    }
	return false;
}

bool	Referee::isCollision(Entity *a, Game &game)
{
  if (playerColision(a, game) || iaColision(a, game) ||
	  wallColision(a, game) || missileColision(a, game))
	  return true;
  return false;
}
