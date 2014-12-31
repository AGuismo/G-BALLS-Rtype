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
	Position(pos x, pos y, dir direction);
	Position(pos position[2], dir direction);
	Position();
	~Position();
	Position(const Position &src);
	Position	&operator=(const Position &src);

public:
	inline pos		x() const;
	inline pos		y() const;
	inline dir		direction() const;

	inline void		x(pos x);
	inline void		y(pos y);
	inline void		direction(dir d);

private:
	pos		_positions[2];
	dir		_dir;
};

