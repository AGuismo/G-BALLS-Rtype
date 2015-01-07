#include	"Mob.hh"

Mob::Mob(unsigned short id, const Position &pos, Entity::minortype mobType,
	velocity v, short hp, short shield) :
	Entity(Entity::createType(Entity::MOBS, mobType), id, pos, v, hp, shield, HEIGHT, WIDTH)
{
	_isMoveable = true;
	_isDestructible = true;
}

Mob::Mob()
{
	_isMoveable = true;
	_isDestructible = true;
	type(createType(MOBS, 0));
}


Mob::~Mob()
{
}

Mob::Mob(const Mob &src) :
Entity(src)
{

}

Mob	&Mob::operator=(const Mob &src)
{
	if (&src != this)
	{
		Entity::operator=(src);
	}
	return (*this);
}
