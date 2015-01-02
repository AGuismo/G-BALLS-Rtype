#include "Position.hh"

Position::Position(pos x, pos y, dir direction):
_dir(direction)
{
	_positions[0] = x;
	_positions[1] = y;
}

Position::Position(pos positions[2], dir direction):
_dir(direction)
{
	_positions[0] = positions[0];
	_positions[1] = positions[1];
}

Position::Position()
{
	_positions[0] = 0;
	_positions[1] = 0;
	_dir = NORTH;
}

Position::~Position()
{
}

Position::Position(const Position &src)
{
	_positions[0] = src._positions[0];
	_positions[1] = src._positions[1];
	_dir = src._dir;
}

Position	&Position::operator=(const Position &src)
{
	if (&src != this)
	{
		_positions[0] = src._positions[0];
		_positions[1] = src._positions[1];
		_dir = src._dir;
	}
	return (*this);
}

Position::pos	Position::x() const
{
	return (_positions[0]);
}

Position::pos	Position::y() const
{
	return (_positions[1]);
}

Position::dir	Position::direction() const
{
	return (_dir);
}

void		Position::x(pos x)
{
	_positions[0] = x;
}

void		Position::y(pos y)
{
	_positions[1] = y;
}

void		Position::direction(dir direction)
{
	_dir = direction;
}
