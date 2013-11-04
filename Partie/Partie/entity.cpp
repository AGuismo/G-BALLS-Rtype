#include "entity.h"

Entity::Entity(TYPE type, int x, int y, int life, DIR dir, int length, int height) :
		_life(life), _dir(dir), _speed(1), _length(length), _height(height)
{
	static int id = 0;

	_type = type;
	_posx = x;
	_posy = y;
	_id = id;
	id++;
}

Entity::~Entity()
{

}

void	Entity::update()
{
	if (_dir == NORTH || _dir == NORTH_WEST || _dir == NORTH_EAST)
		_posy -=	 1;
	if (_dir == SOUTH || _dir == SOUTH_WEST || _dir == SOUTH_EAST)
		_posy += 1;
	if (_dir == WEST || _dir == NORTH_WEST || _dir == SOUTH_WEST)
		_posx -= 1;
	if (_dir == EAST || _dir == SOUTH_EAST || _dir == NORTH_EAST)
		_posx += 1;
}