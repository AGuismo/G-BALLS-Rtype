#pragma once

#include	"Entity.h"

class Missile;
class AIaAlgo;

class Ia : public Entity
{
 public:
    Ia(game::ID id, AIaAlgo *algo);
  virtual ~Ia();
  void		update(Game &game);
  void		move();
  void		fire(Game &game, bool charged);
  AIaAlgo	*algo() { return _algo; }

 private:
  AIaAlgo	*_algo;
};
