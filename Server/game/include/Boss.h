#pragma once

#include "Entity.h"

class Refere;

class Boss : public Entity
{
public:
	Boss(int x, int y, int life, int length, int heigth);
	~Boss(void);
	
	void	update();
	void	move();
	void	fire();
private:


	friend Refere;
};

