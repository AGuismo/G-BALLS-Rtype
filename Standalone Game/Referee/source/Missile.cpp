#include "Missile.hh"

Missile::Missile(unsigned short id, const Position &pos, unsigned short level,
	velocity v) :
	Entity(Entity::createType(Entity::MISSILE, level), id, pos, v, DEFAULT_HP, DEFAULT_SHIELD, HEIGHT, WIDTH)
{
	_isMoveable = true;
	_isDestructible = true;
}

Missile::Missile()
{
	_isMoveable = true;
	_isDestructible = true;
	type(createType(MISSILE, 0));
}


Missile::~Missile()
{
}

Missile::Missile(const Missile &src) :
Entity(src)
{

}

Missile	&Missile::operator=(const Missile &src)
{
	if (&src != this)
	{
		Entity::operator=(src);
	}
	return (*this);
}
