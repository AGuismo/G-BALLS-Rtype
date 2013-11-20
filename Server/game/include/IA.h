#pragma once

#include	"Entity.h"
#include	"IaAlgo.hh"

class Missile;

class Ia : public Entity
{
 public:
    Ia(game::ID id, AIaAlgo *algo);
  virtual ~Ia();
  void	update();
  void	move();
  Missile	*fire(Game &game, bool charged);
  AIaAlgo	*algo() { return _algo; }

 private:
  AIaAlgo	*_algo;
};
