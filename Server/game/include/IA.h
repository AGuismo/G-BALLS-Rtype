#pragma once

#include	"Entity.h"
#include	"IaAlgo.hh"

class Missile;

class Ia : public Entity
{
 public:
    Ia(game::Pos pos, int life, int length, int height, game::ID id, AIaAlgo *algo);
  virtual ~Ia();
  void	update();
  void	move();
  Missile	*fire(Game &game);
 private:
  AIaAlgo	*_algo;
};
