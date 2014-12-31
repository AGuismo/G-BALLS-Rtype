#include "Player.hh"

Player::Player(unsigned short id, const Position &pos,
			   unsigned short height, unsigned short width,
			   velocity v, short hp, short shield, short playerNo):
			   Entity(Entity::PLAYER, id, pos, height, width), Destructible(hp, shield),
			   Moveable(v), _playerNo(playerNo)
{

}

Player::Player(const Entity &e, const Destructible &d, const Moveable &m, short playerNo):
Entity(e), Destructible(d), Moveable(m), _playerNo(playerNo)
{
	type(PLAYER);
}

Player::Player():
_playerNo(0)
{
	type(PLAYER);
}


Player::~Player()
{
}

Player::Player(const Player &src) :
Entity(src), Destructible(src), Moveable(src), _playerNo(src._playerNo)
{

}

Player	&Player::operator=(const Player &src)
{
	if (&src != this)
	{
		Entity::operator=(src);
		Destructible::operator=(src);
		Moveable::operator=(src);
		_playerNo = src._playerNo;
	}
	return (*this);
}
