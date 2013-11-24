#pragma once

#include "Entity.h"
class Referee;
class AIaAlgo;

class Boss : public Entity
{
public:
	Boss(ID id, AIaAlgo *algo);
  ~Boss(void);

  void	update();
  void	move();
  Missile	*fire(Game &game, bool charged);
  AIaAlgo	*algo() { return _algo; }

private:
	AIaAlgo	*_algo;

  friend class Referee;
};
