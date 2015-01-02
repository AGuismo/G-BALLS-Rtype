#include "Entity.hh"

Entity::Entity(type t, unsigned short id, const Position &pos, unsigned short height, unsigned short width) :
_type(t), _id(id), _p(pos), _height(height), _width(width)
{

}

Entity::Entity():
_type(createType(NONE, 0)), _id(0), _height(0), _width(0)
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

Entity::type	Entity::createType(Entity::majortype maj, Entity::minortype min)
{
	type		t;

	t.desc.maj = maj;
	t.desc.min = min;
	return (t);
}

Entity::type	Entity::getType() const
{
	return (_type);
}

void			Entity::setType(const type &t)
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
