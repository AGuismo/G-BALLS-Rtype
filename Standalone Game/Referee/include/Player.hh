#pragma once
#include	"Entity.hh"

class Player :
	public Entity
{
public:
	static const velocity		DEFAULT_SPEED = 50;
	static const short			DEFAULT_HP = 1;
	static const short			DEFAULT_SHIELD = 0;
	static const unsigned short	HEIGHT = 28;
	static const unsigned short	WIDTH = 64;

public:
	Player(unsigned short id, const Position &pos, unsigned short playerNo = 0,
		   velocity v = DEFAULT_SPEED, short hp = DEFAULT_HP, short shield = DEFAULT_SHIELD);
	Player();
	~Player();

	Player(const Player &src);
	Player	&operator=(const Player &src);

private:
	// step2: associated bonuses
};

