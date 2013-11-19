#include "IA.h"
#include "Game.h"
#include "Missile.h"

Ia::Ia(game::Pos pos, int life, int length, int height, game::ID id) : Entity(game::IA, pos, life, game::WEST, length, height, id)
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
	_dir = (game::Dir)(rand() % 8);
	_prevPos = _pos;
	if (_dir == game::NORTH || _dir == game::NORTH_WEST || _dir == game::NORTH_EAST)
		_pos -= SIZE;
	if (_dir == game::SOUTH || _dir == game::SOUTH_WEST || _dir == game::SOUTH_EAST)
		_pos += SIZE;
	if (_dir == game::WEST || _dir == game::NORTH_WEST || _dir == game::SOUTH_WEST)
		_pos -= 1;
	if (_dir == game::EAST || _dir == game::SOUTH_EAST || _dir == game::NORTH_EAST)
		_pos += 1;
}

Missile	*Ia::fire(Game &game)
{
	return (new Missile(*this, game::WEST, _pos, game.UniqueId()));
}