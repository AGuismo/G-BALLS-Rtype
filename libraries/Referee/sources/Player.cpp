#if defined(DEBUG)
# include	<stdexcept>
#endif // !DEBUG
#include "Player.hh"

Player::Player(unsigned short id, const Position &pos, unsigned short playerNo,
			   velocity v, short hp, short shield):
			   Entity(Entity::createType(Entity::PLAYER, playerNo), id, pos, v, hp, shield, HEIGHT, WIDTH)
{
	_isMoveable = true;
	_isDestructible = true;
#if defined(DEBUG)
	if (playerNo == 0 || playerNo > 4)
		throw std::runtime_error("Player::Player(): Player must have a No between 1 and 4.");
#endif

}

Player::Player()
{
	_isMoveable = true;
	_isDestructible = true;
	type(createType(PLAYER, 0));
}


Player::~Player()
{
}

Player::Player(const Player &src) :
Entity(src)
{

}

Player::Player(const Entity &src_base):
Entity(src_base)
{

}

Player	&Player::operator=(const Player &src)
{
	if (&src != this)
	{
		Entity::operator=(src);
	}
	return (*this);
}

void	Player::serialize(Protocol &p) const
{
	Entity::serialize(p);
	//p << ;
}

void	Player::unserialize(Protocol &p)
{
	Entity::unserialize(p);
	//p >> ;
}

Entity	*Player::copy() const
{
	return (new Player(*this));
}
