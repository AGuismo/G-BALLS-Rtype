#include "Player.h"

Player::Player(int x, int y/*, udp*/) : Entity(PLAYER, x, y, 1, EAST, 1, 1)
{
	_pow = 0;
	_extraLife = false;
	//_udp = udp;
	std::cout << "A new character is comming" << std::endl;
}

Player::~Player()
{
	std::cout << "A player is dead" << std::endl;
}

void	Player::move(DIR dir, int speed)
{
	_dir = dir;
	_speed = speed;
}

Missile *Player::fire()
{
	Missile *boom = new Missile(*this, EAST, _posx, _posy);

	return boom;
}

