#include "Entity.hh"

Entity::Entity(type t, unsigned short id, const Position &pos, unsigned short height, unsigned short width) :
_type(t), _id(id), _p(pos), _height(height), _width(width)
{

}

Entity::Entity():
_type(NONE), _id(0), _height(0), _width(0)
{

}

Entity::~Entity()
{

}

Entity::Entity(const Entity &src) :
_type(src._type), _id(src._id), _p(src._p), _height(src._height), _width(src._width)
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
	}
	return (*this);
}