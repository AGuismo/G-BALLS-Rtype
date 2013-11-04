#include "Partie.h"

Partie::Partie(std::list<Player *> players)
{
	_players = players;
	_titan = NULL;
}

Partie::~Partie()
{

}

void	Partie::update()
{
	std::list<Player *>::iterator itp = _players.begin();
	std::list<Ia *>::iterator itia = _IA.begin();
	std::list<Entity *>::iterator ite = _objs.begin();
	std::list<Missile *>::iterator itm = _missiles.begin();

/*	for (itp; itp != _players.end(); itp++)
	{
		(*itp)->update();
		if (Refere::isCollision(*itp, *this) == true)
		{
			if ((*itp)->_extraLife == true)
				(*itp)->_extraLife = false;
			else
			{
				delete *itp;
				_players.erase(itp);
			}
		}
	}*/
	for (itia; itia != _IA.end(); itia++)
	{
		(*itia)->update();
		if (Refere::isCollision(*itia, *this) == true)
		{
			(*ite)->_life--;
			if ((*ite)->_life <= 0)
			{
				delete *itia;
				_IA.erase(itia);
			}
		}
	}
	for (ite; ite != _objs.end(); ite++)
	{
		(*ite)->update();
		if (Refere::isCollision(*ite, *this) == true)
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
	for (itm; itm != _missiles.end(); itm++)
	{
		for (int i = 0;i < (*itm)->_speed; i++)
		{
			(*itm)->update();
			if (Refere::isCollision(*itm, *this) == true)
			{
				delete *itm;
				_missiles.erase(itm);
			}
		}
	}
	if (_titan)
	{
		_titan->update();
		if (Refere::isCollision(_titan, *this))
		{

		}
	}
}