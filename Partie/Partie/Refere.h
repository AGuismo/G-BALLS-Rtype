#pragma once

#include	"Entity.h"

class Partie;

class Refere
{
public:
	Refere();
	~Refere();
	void	update(Partie &game);
	static bool	isCollision(Entity *a, Partie &game);
private:
	void	getIA();
	void	getBoss();
	static bool	sameCase(const Entity *a, const Entity *b);
	static bool isOnScreen(const Entity *a);

	static const int RIGHTSIDE = 42;
	static const int LEFTSIDE = -42;
	static const int TOPSIDE = -42;
	static const int BOTTOMSIDE = 42;
};