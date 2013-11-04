#include "Boss.h"

Boss::Boss(int x, int y, int life, int length, int heigth) :
	Entity(BOSS, x, y, life, WEST, length, heigth)
{
}


Boss::~Boss(void)
{
}
