#include "Boss.h"

Boss::Boss(int pos, int life, int length, int heigth) :
  Entity(BOSS, pos, life, WEST, length, heigth)
{
}


Boss::~Boss(void)
{
}
