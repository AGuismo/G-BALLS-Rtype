#include	"Referee.h"
#include	"Game.h"
#include	"Player.h"
#include	"Missile.h"
#include	"DeathRequest.h"
#include	"IA.h"
#include	"Bonus.h"
#include	"Boss.h"
#include	"VictoryRequest.h"
#include	"BuffRequest.h"
#include	"NextStage.hh"
#include	"Env.hh"

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
		game::Pos p = *ita;
		game::Pos pp = *itprev;
		if (((p) % rtype::Env::getInstance().game.mapSize + 1 != pp % rtype::Env::getInstance().game.mapSize &&
			(p) % rtype::Env::getInstance().game.mapSize - 1 != pp % rtype::Env::getInstance().game.mapSize &&
			(p) + rtype::Env::getInstance().game.mapSize != pp&&
			(p) - rtype::Env::getInstance().game.mapSize != pp &&
			p != pp) || p < 0 || p > rtype::Env::getInstance().game.mapSize * rtype::Env::getInstance().game.mapSize - 1)
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
	  if ((*itp)->alive())
	  {
		  if (a->_type == requestCode::game::server::BONUS)
		  {
			  game._toSend.requestPush(new BuffRequest((*itp)->player()->id(), dynamic_cast<game::ABonus *>(a)->typeb()));
			  dynamic_cast<game::ABonus *>(a)->applyBuff((*itp)->player());
		  }
		  else if (a->_type != requestCode::game::server::PLAYER && a->_type != requestCode::game::server::MISSILE &&
			  sameCase(a, (*itp)->player()) == true)
		  {
			  if ((*itp)->player()->_extraLife == true)
				  (*itp)->player()->_extraLife = false;
			  else
			  {
				  game.pushRequest(new DeathRequest((*itp)->player()->id()));
				  (*itp)->_alive = false;
			  }
			  return true;
		  }
		  else if (a->_type == requestCode::game::server::MISSILE &&
			  sameCase(a, (*itp)->player()) == true)
		  {
			  if ((dynamic_cast<Missile *>(a))->getLauncher()->_type != requestCode::game::server::PLAYER)
			  {
				  game.pushRequest(new DeathRequest((*itp)->player()->id()));
				  (*itp)->_alive = false;
				  return true;
			  }
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
	  if (a->_type != requestCode::game::server::IA && a->_type != requestCode::game::server::MISSILE &&
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
	  else if (a->_type == requestCode::game::server::MISSILE &&
	       sameCase(a, *itia) == true)
		{
		  if (dynamic_cast<Missile *>(a)->getLauncher()->_type != requestCode::game::server::IA)
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
  std::list<Entity *>::iterator itwall = game._objs.begin();

  for (; itwall != game._objs.end(); itwall++)
    {
	  if (a->_type != requestCode::game::server::INDESTRUCTIBLE_WALL && a->_type != requestCode::game::server::DESTRUCTIBLE_WALL &&
	  sameCase(a, *itwall) == true)
		{
		  if ((*itwall)->_type != requestCode::game::server::INDESTRUCTIBLE_WALL && (*itwall)->_type != requestCode::game::server::DESTRUCTIBLE_WALL)
			{
			  (*itwall)->_life--;
			if ((*itwall)->_life <= 0)
				{
				  game.randBonnus(*(*itwall));
				  game.pushRequest(new DeathRequest((*itwall)->id()));
				  delete *itwall;
				  itwall = game._objs.erase(itwall);
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
	  if (a->_type != requestCode::game::server::MISSILE &&
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
		if (a->_type == requestCode::game::server::PLAYER &&
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

bool		Referee::bossCollision(Entity *a, Game &game)
{
    if (!game._titan)
	return false;
	if (a->_type != requestCode::game::server::IA && a->_type != requestCode::game::server::MISSILE &&
	sameCase(a, game._titan) == true)
    {
	game._titan->_life--;
	if (game._titan->_life <= 0)
	{
	    game.pushRequest(new DeathRequest(game._titan->id()));
	    if (game._titans.empty())
		game.pushRequest(new VictoryRequest());
	    else
	    {
		game.pushRequest(new NextStageRequest());
		game._clock.restart();
	    }
	    delete game._titan;
	}
	return true;
    }
    else if (a->_type == requestCode::game::server::MISSILE &&
	     sameCase(a, game._titan) == true)
    {
		if (dynamic_cast<Missile *>(a)->getLauncher()->_type != requestCode::game::server::IA)
	{
	    game._titan->_life--;
	    if (game._titan->_life <= 0)
	    {
		game.pushRequest(new DeathRequest(game._titan->id()));
		if (game._titans.empty())
		    game.pushRequest(new VictoryRequest());
		else
		{
		    game.pushRequest(new NextStageRequest());
		    game._clock.restart();
		}
		delete game._titan;
	    }
	    return true;
	}
    }
    return false;
}

bool		Referee::isCollision(Entity *a, Game &game)
{
  if (playerCollision(a, game) || iaCollision(a, game) ||
      wallCollision(a, game) || missileCollision(a, game) ||
	  bossCollision(a, game))
    return true;
  bonusCollision(a, game);
  return false;
}

bool		Referee::asAlivePlayers(Game &game)
{
	std::list<game::Client *>::iterator it;

	for (it = game.clients().begin(); it != game.clients().end(); it++)
	{
		if ((*it)->alive() == true)
			return true;
	}
	return false;
}
