#include "Moveable.hh"


Moveable::Moveable(velocity v):
_velocity(v)
{
}

Moveable::Moveable()
{
}

Moveable::~Moveable()
{
}

Moveable::Moveable(const Moveable &src):
_velocity(src._velocity)
{

}
Moveable	&Moveable::operator=(const Moveable &src)
{
	if (&src != this)
	{
		_velocity = src._velocity;
	}
	return (*this);
}

Moveable::velocity	Moveable::speed() const
{
	return (_velocity);
}

void		Moveable::speed(velocity v)
{
	_velocity = v;
}
