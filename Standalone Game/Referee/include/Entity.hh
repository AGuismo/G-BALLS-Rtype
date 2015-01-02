#pragma once

#include	"Position.hh"

class Entity
{
public:
	enum majortype : unsigned char
	{
		NONE,
		PLAYER,
		BOSS,
		MOBS,
		WALL,
		BONUS,
		MISSILE
	};

	typedef unsigned char	minortype;

	union	type
	{
		struct
		{
			majortype	maj;
			minortype	min;
		}				desc;
		unsigned short	full;
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
	static type	createType(majortype maj, minortype min = 0);

public:
	bool	isMoveable() const;

public:
	type			getType() const;
	void			setType(const type &t);
	unsigned short	getID() const;
	void			setID(unsigned short ID);
	Position		getPosition() const;
	void			setPosition(const Position &pos);
	unsigned short	getHeight() const;
	void			setHeight(unsigned short Height);
	unsigned short	getWidth() const;
	void			setWidth(unsigned short Width);

protected:
	type			_type;
	unsigned short	_id;
	Position		_p;
	unsigned short	_height;
	unsigned short	_width;
};

