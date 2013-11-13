#include "IA.h"

Ia::Ia(int pos, int life, int length, int height) : Entity(IA, pos, life, WEST, length, height)
{
}

Ia::~Ia()
{
}

void	Ia::update()
{
	move();
}

void	Ia::move()
{
	_dir = (DIR)(rand() % 8);
	_prevPos = _pos;
	if (_dir == NORTH || _dir == NORTH_WEST || _dir == NORTH_EAST)
		_pos -= SIZE;
	if (_dir == SOUTH || _dir == SOUTH_WEST || _dir == SOUTH_EAST)
		_pos += SIZE;
	if (_dir == WEST || _dir == NORTH_WEST || _dir == SOUTH_WEST)
		_pos -= 1;
	if (_dir == EAST || _dir == SOUTH_EAST || _dir == NORTH_EAST)
		_pos += 1;
}

Missile	*Ia::fire()
{
	return NULL;
}