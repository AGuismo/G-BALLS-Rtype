#include "Entity.h"

Entity::Entity(game::Type type, game::Pos pos, int life, game::Dir dir,
	       int length, int height, game::ID id) :
  _life(life), _dir(dir), _speed(1), _length(length), _height(height)
{
  _type = type;
  _pos = pos;
  _id = id;
}

Entity::~Entity()
{

}

void	Entity::update()
{
	_prevPos = _pos;
  if (_dir == 0 || _dir == 1 || _dir == 7)
    _pos -=	SIZE;
  if (_dir == 4 || _dir == 5 || _dir == 3)
    _pos += SIZE;
  if (_dir == 6 || _dir == 1 || _dir == 5)
    _pos -= 1;
  if (_dir == 2 || _dir == 3 || _dir == 7)
    _pos += 1;
}
