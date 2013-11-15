#pragma once

#include "Entity.h"

class Referee;

class Boss : public Entity
{
public:
  Boss(int pos, int life, int length, int heigth, ID id);
  ~Boss(void);

/* void	update();
  void	move();
  Missile	*fire();*/

private:


  friend class Referee;
};
