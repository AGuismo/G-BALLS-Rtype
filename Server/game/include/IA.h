#pragma once

#include	"Entity.h"

class Missile;

class Ia : public Entity
{
 public:
  Ia(game::Pos pos, int life, int length, int height, game::ID id);
  virtual ~Ia();
  void	update();
  void	move();
  Missile	*fire();
 private:
};
