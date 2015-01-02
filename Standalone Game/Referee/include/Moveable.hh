#pragma once
class Moveable
{
public:
	typedef short	velocity;

public:
	Moveable(velocity v);
	Moveable();
	virtual ~Moveable();

	Moveable(const Moveable &src);
	Moveable	&operator=(const Moveable &src);

public:
	velocity	speed() const;
	void		speed(velocity v);

protected:
	velocity	_velocity;
};

