#include	"Referee.h"
#include	"Game.h"
#include	"Player.h"
#include	"Missile.h"
#include	"DeathRequest.h"
#include	"IA.h"
#include	"Bonus.h"
#include	"BuffRequest.h"

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
	std::vector<game::Pos>::const_iterator ita;
	std::vector<game::Pos>::const_iterator itprev = a->_prevPos.begin();

	for (ita = a->_pos.begin(); ita != a->_pos.end(); ita++)
	{
		if ((*ita) + 1 != (*itprev) ||
			(*ita) - 1 != (*itprev) ||
			(*ita) != (*itprev))
			return false;
		itprev++;
	}
	return true;
}

bool	Referee::sameCase(const Entity *a, const Entity *b)
{
	std::vector<game::Pos>::const_iterator ita;
	std::vector<game::Pos>::const_iterator itb;

	for (ita = a->_pos.begin(); ita != a->_pos.end(); ita++)
	{
		for (itb = b->_pos.begin(); itb != b->_pos.end(); itb++)
		{
			if ((*ita) == (*itb))
			{
				return true;
			}
		}
	}
	return false;
}


bool	Referee::playerCollision(Entity *a, Game &game)
{
  std::list<game::Client *>::iterator itp = game._players.begin();

  for (; itp != game._players.end(); itp++)
    {
	if (a->_type == game::BONUS)
	{
	    game._toSend.requestPush(new BuffRequest((*itp)->player()->id(), dynamic_cast<game::ABonus *>(a)->typeb()));
	    dynamic_cast<game::ABonus *>(a)->applyBuff((*itp)->player());
	}
	else if (a->_type != game::PLAYER && a->_type != game::MISSILE &&
	  sameCase(a, (*itp)->player()) == true)
	{
	  if ((*itp)->player()->_extraLife == true)
		  (*itp)->player()->_extraLife = false;
	  else
	    {
		  game.pushRequest(new DeathRequest((*itp)->player()->id()));
	      delete *itp;
	      game._players.erase(itp);
	    }
	  return true;
	}
      else if (a->_type == game::MISSILE &&
		  sameCase(a, (*itp)->player()) == true)
	{
	  if ((dynamic_cast<Missile *>(a))->getLauncher()->_type != game::PLAYER)
	    {
		  game.pushRequest(new DeathRequest((*itp)->player()->id()));
		  delete *itp;
	      game._players.erase(itp);
	      return true;
	    }
	}
    }
  return false;
}

bool		Referee::iaCollision(Entity *a, Game &game)
{
  std::list<Ia *>::iterator itia = game._IA.begin();

  for (; itia != game._IA.end(); itia++)
    {
      if (a->_type != game::IA && a->_type != game::MISSILE &&
	  sameCase(a, *itia) == true)
		{
		  (*itia)->_life--;
		  if ((*itia)->_life <= 0)
			{
			    game.randBonnus(*(*itia));
			  game.pushRequest(new DeathRequest((*itia)->id()));
			  delete *itia;
			  game._IA.erase(itia);
			}
		  return true;
		}
      else if (a->_type == game::MISSILE &&
	       sameCase(a, *itia) == true)
		{
		  if (dynamic_cast<Missile *>(a)->getLauncher()->_type != game::IA)
			{
			  (*itia)->_life--;
			  if ((*itia)->_life <= 0)
				{
				    game.randBonnus(*(*itia));
					game.pushRequest(new DeathRequest((*itia)->id()));
					delete *itia;
					game._IA.erase(itia);
				}
				return true;
			}
		}
    }
  return false;
}
bool		Referee::wallCollision(Entity *a, Game &game)
{
  std::list<Entity *>::iterator ite = game._objs.begin();

  for (; ite != game._objs.end(); ite++)
    {
      if (a->_type != game::WALL && a->_type != game::DESTRUCTIBLEWALL &&
	  sameCase(a, *ite) == true)
		{
		  if ((*ite)->_type != game::WALL)
			{
			  (*ite)->_life--;
			if ((*ite)->_life <= 0)
				{
				    game.randBonnus(*(*ite));
				  game.pushRequest(new DeathRequest((*ite)->id()));
				  delete *ite;
				  ite = game._objs.erase(ite);
				}
			}
		  return true;
		}
    }
  return false;
}

bool		Referee::missileCollision(Entity *a, Game &game)
{
  std::list<Missile *>::iterator itm = game._missiles.begin();

  for (; itm != game._missiles.end(); )
    {
	  if (a->_type != game::MISSILE &&
		  sameCase(a, *itm) == true)
	  {
		  game._toSend.requestPush(new DeathRequest((*itm)->id()));
		  delete *itm;
		  itm = game._missiles.erase(itm);
		  return true;
	  }
	  else
		  ++itm;
    }
  return false;
}

bool		Referee::bonusCollision(Entity *a, Game &game)
{
	std::list<game::ABonus *>::iterator itb = game._bonus.begin();

	for (; itb != game._bonus.end(); )
	{
		if (a->_type == game::PLAYER &&
			sameCase(a, *itb) == true)
		{
		    game._toSend.requestPush(new BuffRequest(a->id(), (*itb)->typeb()));
			(*itb)->applyBuff(dynamic_cast<game::Player *>(a));
			delete *itb;
			itb = game._bonus.erase(itb);
			return true;
		}
		else
			++itb;
	}
	return false;
}

bool		Referee::isCollision(Entity *a, Game &game)
{
  if (playerCollision(a, game) || iaCollision(a, game) ||
      wallCollision(a, game) || missileCollision(a, game) || bonusCollision(a, game))
    return true;
  return false;
}
