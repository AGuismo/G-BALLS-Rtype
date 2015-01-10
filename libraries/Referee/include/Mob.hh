#pragma once

#include	"Entity.hh"

class Protocol;

class Mob : public Entity
{
public:
	static const velocity		DEFAULT_SPEED = 80;
	static const short			DEFAULT_HP = 1;
	static const short			DEFAULT_SHIELD = 0;
	static const unsigned short	HEIGHT = 42;
	static const unsigned short	WIDTH = 48;

public:
	Mob(unsigned short id, const Position &pos, Entity::minortype mobType = 0,
		velocity v = DEFAULT_SPEED, short hp = DEFAULT_HP, short shield = DEFAULT_SHIELD);
	Mob();
	~Mob();

	Mob(const Entity &src_base);
	Mob(const Mob &src);
	Mob	&operator=(const Mob &src);

private:

};

