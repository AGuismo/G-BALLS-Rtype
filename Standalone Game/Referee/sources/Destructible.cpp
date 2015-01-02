#include "Destructible.hh"


Destructible::Destructible(short hp, short shield):
_hp(hp), _shield(shield)
{
}

Destructible::~Destructible()
{
}

Destructible::Destructible(const Destructible &src):
_hp(src._hp), _shield(src._shield)
{

}

Destructible	&Destructible::operator=(const Destructible &src)
{
	if (&src != this)
	{
		_hp = src._hp;
		_shield = src._shield;
	}
	return (*this);
}

short	Destructible::hp() const
{
	return (_hp);
}

void	Destructible::hp(short hp)
{
	_hp = hp;
}

short	Destructible::shield() const
{
	return (_shield);
}

void	Destructible::shield(short shield)
{
	_shield = shield;
}
