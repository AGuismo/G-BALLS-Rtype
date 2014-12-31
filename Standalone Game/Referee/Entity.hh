#pragma once

#include	"Position.hh"

class Entity
{
public:
	enum type
	{
		NONE,
		PLAYER,
		BOSS,
		MOBS,
		WALL,
		BONUS,
		MISSILE
	};

public:
	Entity(type t, unsigned short id, const Position &pos,
		   unsigned short height, unsigned short width);
	Entity();
	virtual ~Entity();

public:
	Entity(const Entity &src);
	Entity	&operator=(const Entity &src);

public:
	// get, set

protected:
	type			_type;
	unsigned short	_id;
	Position		_p;
	unsigned short	_height;
	unsigned short	_width;
};

