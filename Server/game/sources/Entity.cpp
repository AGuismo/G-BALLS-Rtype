#include "Entity.h"

Entity::Entity(game::Type type, std::vector<game::Pos> pos, int life, game::Dir dir,
	       game::ID id) :
  _life(life), _dir(dir), _speed(1)
{
  _type = type;
  _pos = pos;
  _id = id;
}

Entity::~Entity()
{

}

game::ID		&Entity::id()
{
	return _id;
}

game::Type		&Entity::type()
{
	return _type;
}

game::Dir		&Entity::dir()
{
	return _dir;
}
std::vector<game::Pos>		&Entity::pos()
{
	return _pos;
}


void	Entity::update()
{
	std::vector<game::Pos>::iterator it = _pos.begin();
	
	_prevPos = _pos;
	if (_dir == game::NORTH || _dir == game::NORTH_WEST || _dir == game::NORTH_EAST)
		for (; it != _pos.end(); it++)
			(*it) -=	SIZE;
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
