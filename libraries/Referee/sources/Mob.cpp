#include	"Mob.hh"

Mob::Mob(unsigned short id, const Position &pos, entity::MinorType mobType,
	velocity v, short hp, short shield) :
	Entity(Entity::createType(entity::MOBS, mobType), id, pos, v, hp, shield, HEIGHT, WIDTH)
{
	_isMoveable = true;
	_isDestructible = true;
}

Mob::Mob()
{
	_isMoveable = true;
	_isDestructible = true;
	setType(createType(entity::MOBS, 0));
}


Mob::~Mob()
{
}

Mob::Mob(const Mob &src) :
Entity(src)
{

}

Mob::Mob(const Entity &src_base) :
Entity(src_base)
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
