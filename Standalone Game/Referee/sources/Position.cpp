#include "Position.hh"

Position::Position(pos pos_x, pos pos_y, dir direction):
x(pos_x), y(pos_y), _dir(direction)
{
}

Position::Position():
x(0), y(0)
{
	_dir = NORTH;
}

Position::~Position()
{
}

Position::Position(const Position &src)
{
	x = src.x;
	y = src.y;
	_dir = src._dir;
}

Position	&Position::operator=(const Position &src)
{
	if (&src != this)
	{
		x = src.x;
		y = src.y;
		_dir = src._dir;
	}
	return (*this);
}

Position::dir	Position::direction() const
{
	return (_dir);
}

void		Position::direction(dir direction)
{
	_dir = direction;
}

bool		Position::operator==(const Position &rhs)
{
	return (x == rhs.x && y == rhs.y);
}

bool		Position::operator!=(const Position &rhs)
{
	return (!operator==(rhs));
}

Position	&Position::operator+=(const Position &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return (*this);
}

Position	&Position::operator-=(const Position &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return (*this);
}

Position	Position::operator+(const Position &rhs)
{
	return (Position(x + rhs.x, y + rhs.y));
}

Position	Position::operator-(const Position &rhs)
{
	return (Position(x - rhs.x, y - rhs.y));
}
