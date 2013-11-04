#include "Refere.h"
#include "Partie.h"

Refere::Refere()
{

}

Refere::~Refere()
{

}

void	Refere::update(Partie &game)
{

}

void	Refere::getIA()
{

}

void	Refere::getBoss()
{

}

bool	Refere::sameCase(const Entity *a, const Entity *b)
{
	if (a->_posx <= b->_posx &&
		a->_posx + a->_length >= b->_posx &&
		a->_posy <= b->_posy &&
		a->_posy + a->_height >= b->_posy)
		return true;
	if (a->_posx <= b->_posx + b->_length &&
		a->_posx + a->_length >= b->_posx + b->_length &&
		a->_posy <= b->_posy &&
		a->_posy + a->_height >= b->_posy)
		return true;
	if (a->_posx <= b->_posx &&
		a->_posx + a->_length >= b->_posx &&
		a->_posy <= b->_posy + b->_height &&
		a->_posy + a->_height >= b->_posy + b->_height)
		return true;
	if (a->_posx <= b->_posx + b->_length &&
		a->_posx + a->_length >= b->_posx + b->_length &&
		a->_posy <= b->_posy + b->_height &&
		a->_posy + a->_height >= b->_posy + b->_height)
		return true;
	return false;
}

bool	Refere::isOnScreen(const Entity *a)
{
	if (a->_type != PLAYER &&
		(a->_posx + a->_length <= LEFTSIDE ||
		 a->_posx >= RIGHTSIDE ||
		 a->_posy + a->_height <= TOPSIDE ||
		 a->_posy >= BOTTOMSIDE))
		return false;
	return true;
}

bool	Refere::isCollision(Entity *a, Partie &game)
{
	std::list<Player *>::iterator itp = game._players.begin();
	std::list<Ia *>::iterator itia = game._IA.begin();
	std::list<Entity *>::iterator ite = game._objs.begin();
	std::list<Missile *>::iterator itm = game._missiles.begin();

	if (isOnScreen(a) == false)
		return true;
	for (itp; itp != game._players.end(); itp++)
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
	for (itia; itia != game._IA.end(); itia++)
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
	for (ite; ite != game._objs.end(); ite++)
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
	for (itm; itm != game._missiles.end(); itm++)
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