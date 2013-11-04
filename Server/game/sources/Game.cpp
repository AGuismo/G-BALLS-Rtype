#include "Game.h"

Game::Game(std::list<Player *> players)
{
  _players = players;
  _titan = NULL;
}

Game::~Game()
{

}

void	Game::update()
{
  std::list<Player *>::iterator itp = _players.begin();
  std::list<Ia *>::iterator itia = _IA.begin();
  std::list<Entity *>::iterator ite = _objs.begin();
  std::list<Missile *>::iterator itm = _missiles.begin();

  for (itia = _IA.begin(); itia != _IA.end(); itia++)
    {
      (*itia)->update();
      if (Referee::isCollision(*itia, *this) == true)
	{
	  (*ite)->_life--;
	  if ((*ite)->_life <= 0)
	    {
	      delete *itia;
	      _IA.erase(itia);
	    }
	}
    }
  for (ite = _objs.begin(); ite != _objs.end(); ite++)
    {
      (*ite)->update();
      if (Referee::isCollision(*ite, *this) == true)
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
  for (itm = _missiles.begin(); itm != _missiles.end(); itm++)
    {
      for (unsigned int i = 0;i < (*itm)->_speed; i++)
	{
	  (*itm)->update();
	  if (Referee::isCollision(*itm, *this) == true)
	    {
	      delete *itm;
	      _missiles.erase(itm);
	    }
	}
    }
  if (_titan)
    {
      _titan->update();
      if (Referee::isCollision(_titan, *this))
	{

	}
    }
}
