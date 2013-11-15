#pragma once

#include	"Entity.h"

class Missile;

class Ia : public Entity
{
 public:
  Ia(Ruint16 pos, int life, int length, int height, ID id);
  virtual ~Ia();
  void	update();
  void	move();
  Missile	*fire();
 private:
};
