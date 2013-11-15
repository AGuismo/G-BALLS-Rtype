#include "Boss.h"

Boss::Boss(int pos, int life, int length, int heigth, ID id) :
  Entity(BOSS, pos, life, WEST, length, heigth, id)
{
}


Boss::~Boss(void)
{
}
