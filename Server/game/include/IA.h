#pragma once

#include	"Entity.h"

class Ia : public Entity
{
 public:
  Ia(int x, int y, int life, int length, int height);
  virtual ~Ia();
  void	update();
  void	move();
  void	fire();
 private:
};
