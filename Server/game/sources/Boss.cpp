#include "Boss.h"

Boss::Boss(int pos, int life, int length, int heigth, ID id) :
  Entity(game::BOSS, pos, life, game::WEST, length, heigth, id)
{
}


Boss::~Boss(void)
{
}
