#pragma once
class Position
{
public:
	typedef unsigned short	pos;
	typedef unsigned short	dir;

public:
	enum default_directions : dir
	{
		NORTH = 0,
		NORTH_EAST = 45,
		EAST = 90,
		SOUTH_EAST = 135,
		SOUTH = 180,
		SOUTH_WEST = 225,
		WEST = 270,
		NORTH_WEST = 315,
	};

public:
	Position(pos x, pos y, dir direction = 0);
	Position();
	~Position();
	Position(const Position &src);
	Position	&operator=(const Position &src);

public:
	bool	operator==(const Position &rhs);
	bool	operator!=(const Position &rhs);

public:
	Position	&operator+=(const Position &rhs);
	Position	&operator-=(const Position &rhs);

	Position	operator+(const Position &rhs);
	Position	operator-(const Position &rhs);

public:
	pos		x;
	pos		y;
	dir		direction;
};

