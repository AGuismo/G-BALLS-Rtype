#include "Missile.hh"

Missile::Missile(unsigned short id, const Position &pos, unsigned short level,
		 velocity v) :
  Entity(Entity::createType(entity::MISSILE, level), id, pos, v, DEFAULT_HP, DEFAULT_SHIELD, 0, 0)
{
  _isMoveable = true;
  _isDestructible = true;
  switch (level)
  {
  case 1:
    _height = 16;
    _width = 32;
    break;
  case 2:
    _height = 20;
    _width = 64;
    break;
  case 3:
    _height = 24;
    _width = 96;
    break;
  case 4:
    _height = 28;
    _width = 128;
    break;
  default:
    break;
  }
}

Missile::Missile()
{
  _isMoveable = true;
  _isDestructible = true;
  setType(Entity::createType(entity::MISSILE, 0));
}


Missile::~Missile()
{
}

Missile::Missile(const Missile &src) :
  Entity(src)
{

}

Missile::Missile(const Entity &src_base) :
  Entity(src_base)
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
