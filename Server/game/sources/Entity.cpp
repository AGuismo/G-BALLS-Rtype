#include "Entity.h"

Entity::Entity(game::Type type, std::vector<game::Pos> pos, int life, game::Dir dir,
	       int length, int height, game::ID id) :
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
	if (_dir == 0 || _dir == 1 || _dir == 7)
		for (;it != _pos.end(); it++)
			(*it) -=	SIZE;
	if (_dir == 4 || _dir == 5 || _dir == 3)
		for (; it != _pos.end(); it++)
			(*it) += SIZE;
	if (_dir == 6 || _dir == 1 || _dir == 5)
		for (; it != _pos.end(); it++)
			(*it) -= 1;
	if (_dir == 2 || _dir == 3 || _dir == 7)
		for (; it != _pos.end(); it++)
			(*it) += 1;
}
