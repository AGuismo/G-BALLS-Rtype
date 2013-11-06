#pragma once

#include	"Entity.h"

class Ia : public Entity
{
 public:
  Ia(int pos, int life, int length, int height);
  virtual ~Ia();
  void	update();
  void	move();
  void	fire();
 private:
};
