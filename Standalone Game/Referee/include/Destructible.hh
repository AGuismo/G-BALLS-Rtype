#pragma once
class Destructible
{
public:
	Destructible(short hp = 1, short shield = 0);
	virtual ~Destructible();

	Destructible(const Destructible &src);
	Destructible	&operator=(const Destructible &src);

public:
	short	hp() const;
	void	hp(short hp);
	short	shield() const;
	void	shield(short shield);

protected:
	short	_hp;
	short	_shield;
};

