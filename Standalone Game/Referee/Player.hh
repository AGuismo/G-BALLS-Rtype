#pragma once
#include	"Entity.hh"
#include	"Destructible.hh"
#include	"Moveable.hh"

class Player :
	public Entity, public Destructible, public Moveable
{
public:
	static const velocity	DEFAULT_SPEED = 20;

public:
	Player(unsigned short id, const Position &pos,
		   unsigned short height, unsigned short width,
		   velocity v = DEFAULT_SPEED, short hp = 1, short shield = 0, short playerNo = 0);
	Player(const Entity &e, const Destructible &d, const Moveable &m, short playerNo = 0);
	Player();
	~Player();

	Player(const Player &src);
	Player	&operator=(const Player &src);

private:
	short	_playerNo;
	// step2: associated bonuses
};

