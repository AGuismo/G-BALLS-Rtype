#pragma once
#include	"Entity.hh"

class Protocol;

class Missile :
	public Entity
{
public:
	static const velocity		DEFAULT_SPEED = 100;
	static const unsigned short DEFAULT_LEVEL = 1;
	static const unsigned short DEFAULT_HP = 1;
	static const unsigned short DEFAULT_SHIELD = 1;

public:
	Missile(unsigned short id, const Position &pos, 
		    unsigned short level = DEFAULT_LEVEL, velocity v = DEFAULT_SPEED);
	Missile();
	~Missile();

	Missile(const Entity &src_base);
	Missile(const Missile &src);
	Missile	&operator=(const Missile &src);

private:

};

