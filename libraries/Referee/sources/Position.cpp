#include "Position.hh"

Position::Position(pos pos_x, pos pos_y, dir direction):
x(pos_x), y(pos_y), direction(direction)
{
}

Position::Position():
x(0), y(0)
{
	direction = NORTH;
}

Position::~Position()
{
}

Position::Position(const Position &src)
{
	x = src.x;
	y = src.y;
	direction = src.direction;
}

Position	&Position::operator=(const Position &src)
{
	if (&src != this)
	{
		x = src.x;
		y = src.y;
		direction = src.direction;
	}
	return (*this);
}

bool		Position::operator==(const Position &rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool		Position::operator!=(const Position &rhs) const
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

Position	Position::operator+(const Position &rhs) const
{
	return (Position(x + rhs.x, y + rhs.y));
}

Position	Position::operator-(const Position &rhs) const
{
	return (Position(x - rhs.x, y - rhs.y));
}
