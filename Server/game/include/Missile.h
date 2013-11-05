#pragma once

#include "Entity.h"

class Player;
class Partie;

class Missile : public Entity
{
public:
	Missile(Entity &launcher, DIR dir, int x, int y);
	~Missile();
	Entity *getLauncher() const { return &_launcher;};
private:
	Entity		&_launcher;
	int			_pow;

	friend Partie;
};