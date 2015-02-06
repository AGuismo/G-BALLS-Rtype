#include	"Entity.hh"
#include	"Protocol.hpp"

Entity::Entity(entity::Type t, rtype::protocol::game::ID id,
	       const Position &pos, velocity v, short hp, short shield,
	       unsigned short height, unsigned short width) :
  _type(t), _id(id), _p(pos), _height(height), _width(width),
  _isMoveable(true), _velocity(v), _hp(hp), _shield(shield)
{

}

Entity::Entity():
  _type(createType(entity::NONE, 0)), _id(0), _height(0), _width(0),
  _isMoveable(true), _velocity(0), _hp(1), _shield(0)
{

}

Entity::~Entity()
{

}

Entity::Entity(const Entity &src) :
  _type(src._type), _id(src._id), _p(src._p), _height(src._height), _width(src._width),
  _isMoveable(src._isMoveable), _velocity(src._velocity), _hp(src._hp), _shield(src._shield)
{

}

Entity	&Entity::operator=(const Entity &src)
{
  if (&src != this)
  {
    _type = src._type;
    _id = src._id;
    _p = src._p;
    _height = src._height;
    _width = src._width;
    _isMoveable = src._isMoveable;
    _velocity = src._velocity;
    _hp = src._hp;
    _shield = src._shield;
  }
  return (*this);
}

entity::Type	Entity::createType(entity::MajorType maj, entity::MinorType min)
{
  entity::Type		t;

  t.desc.maj = maj;
  t.desc.min = min;
  return (t);
}

entity::Type	Entity::createType(entity::FullType full)
{
  entity::Type		t;

  t.full = full;
  return (t);
}

entity::Type	Entity::getType() const
{
  return (_type);
}

void			Entity::setType(const entity::Type &t)
{
  _type = t;
}

unsigned short	Entity::getID() const
{
  return (_id);
}
void			Entity::setID(unsigned short ID)
{
  _id = ID;
}

Position		Entity::getPosition() const
{
  return (_p);
}

void			Entity::setPosition(const Position &pos)
{
  _p = pos;
}

unsigned short	Entity::getHeight() const
{
  return (_height);
}

void			Entity::setHeight(unsigned short Height)
{
  _height = Height;
}

unsigned short	Entity::getWidth() const
{
  return (_width);
}

void			Entity::setWidth(unsigned short Width)
{
  _width = Width;
}

bool			Entity::isMoveable() const
{
  return (_isMoveable);
}

short	Entity::hp() const
{
  return (_hp);
}

void	Entity::hp(short hp)
{
  _hp = hp;
}

short	Entity::shield() const
{
  return (_shield);
}

void	Entity::shield(short shield)
{
  _shield = shield;
}

Entity::velocity	Entity::speed() const
{
  return (_velocity);
}

void		Entity::speed(velocity v)
{
  _velocity = v;
}

// Serialization
void	Entity::serialize(Protocol &p) const
{
  p << _type.full << _id << _p.x << _p.y << _p.direction << _velocity << _hp << _shield;
}

void	Entity::unserialize(Protocol &p)
{
  p >> _type.full >> _id >> _p.x >> _p.y >> _p.direction >> _velocity >> _hp >> _shield;
}

Entity	*Entity::copy() const
{
  return (new Entity(*this));
}
