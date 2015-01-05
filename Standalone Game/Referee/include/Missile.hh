#pragma once
#include	"Entity.hh"

class Missile :
	public Entity
{
public:
	static const velocity		DEFAULT_SPEED = 100;
	static const unsigned short DEFAULT_LEVEL = 1;
	static const unsigned short DEFAULT_HP = 1;
	static const unsigned short DEFAULT_SHIELD = 1;
	static const unsigned short	HEIGHT = 16;
	static const unsigned short	WIDTH = 32;

public:
	Missile(unsigned short id, const Position &pos, 
		    unsigned short level = DEFAULT_LEVEL, velocity v = DEFAULT_SPEED);
	Missile();
	~Missile();

	Missile(const Missile &src);
	Missile	&operator=(const Missile &src);

private:
	// step2: associated bonuses
};

