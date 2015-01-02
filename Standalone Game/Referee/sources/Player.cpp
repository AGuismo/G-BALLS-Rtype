#include "Player.hh"

Player::Player(unsigned short id, const Position &pos, unsigned short playerNo,
			   velocity v, short hp, short shield):
			   Entity(Entity::createType(Entity::PLAYER, playerNo), id, pos, HEIGHT, WIDTH), 
			   Destructible(hp, shield), Moveable(v)
{
#if defined(DEBUG)
	if (playerNo == 0 || playerNo > 4)
		throw std::runtime_exception("Player::Player(): Player must have a No between 1 and 4.");
#endif
}

Player::Player(const Entity &e, const Destructible &d, const Moveable &m, unsigned short playerNo):
Entity(e), Destructible(d), Moveable(m)
{
	type(createType(PLAYER, playerNo));
}

Player::Player()
{
	type(createType(PLAYER, 0));
}


Player::~Player()
{
}

Player::Player(const Player &src) :
Entity(src), Destructible(src), Moveable(src)
{

}

Player	&Player::operator=(const Player &src)
{
	if (&src != this)
	{
		Entity::operator=(src);
		Destructible::operator=(src);
		Moveable::operator=(src);
	}
	return (*this);
}
