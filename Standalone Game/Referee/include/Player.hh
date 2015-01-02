#pragma once
#include	"Entity.hh"
#include	"Destructible.hh"
#include	"Moveable.hh"

class Player :
	public Entity, public Destructible, public Moveable
{
public:
	static const velocity		DEFAULT_SPEED = 20;
	static const unsigned short	HEIGHT = 28;
	static const unsigned short	WIDTH = 64;

public:
	Player(unsigned short id, const Position &pos, unsigned short playerNo = 0,
		   velocity v = DEFAULT_SPEED, short hp = 1, short shield = 0);
	Player(const Entity &e, const Destructible &d, const Moveable &m, unsigned short playerNo = 0);
	Player();
	~Player();

	Player(const Player &src);
	Player	&operator=(const Player &src);

private:
	// step2: associated bonuses
};

