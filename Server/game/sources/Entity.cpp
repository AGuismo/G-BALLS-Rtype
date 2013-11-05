#include "Entity.h"

Entity::Entity(TYPE type, int pos, int life, DIR dir, int length, int height) :
  _life(life), _dir(dir), _speed(1), _length(length), _height(height)
{
  static int id = 0;

  _type = type;
  _pos = pos;
  _id = id;
  id++;
}

Entity::~Entity()
{

}

void	Entity::update()
{
	_prevPos = _pos;
  if (_dir == NORTH || _dir == NORTH_WEST || _dir == NORTH_EAST)
    _pos -=	SIZE;
  if (_dir == SOUTH || _dir == SOUTH_WEST || _dir == SOUTH_EAST)
    _pos += SIZE;
  if (_dir == WEST || _dir == NORTH_WEST || _dir == SOUTH_WEST)
    _pos -= 1;
  if (_dir == EAST || _dir == SOUTH_EAST || _dir == NORTH_EAST)
    _pos += 1;
}
