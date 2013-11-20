#include "IA.h"
#include "Game.h"
#include "Missile.h"

Ia::Ia(game::ID id, AIaAlgo *algo) : Entity(game::IA, algo->pos(), algo->life(), game::WEST, id), _algo(algo)
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
	std::vector<game::Pos>::iterator it = _pos.begin();

	_prevPos = _pos;
    if (_dir == game::NORTH || _dir == game::NORTH_WEST || _dir == game::NORTH_EAST)
		for (; it != _pos.end(); it++)
			(*it) -= SIZE;
    if (_dir == game::SOUTH || _dir == game::SOUTH_WEST || _dir == game::SOUTH_EAST)
		for (; it != _pos.end(); it++)
			(*it) += SIZE;
    if (_dir == game::WEST || _dir == game::NORTH_WEST || _dir == game::SOUTH_WEST)
		for (; it != _pos.end(); it++)
			(*it) -= 1;
    if (_dir == game::EAST || _dir == game::SOUTH_EAST || _dir == game::NORTH_EAST)
		for (; it != _pos.end(); it++)
			(*it) += 1;
}

Missile	*Ia::fire(Game &game, bool charged)
{
	std::vector<game::Pos> pos;

	pos.push_back(_algo->firePos());
	if (charged)
		pos.push_back(_algo->firePos() + 1);
	return (new Missile(*this, game::WEST, pos, game.UniqueId()));
}
