#pragma once

#include "Entity.h"
#include "BossAlgo.h"
class Referee;

class Boss : public Entity
{
public:
	Boss(ID id, ABossAlgo *algo);
  ~Boss(void);

  void	update();
  void	move();
  Missile	*fire(Game &game, bool charged);
  ABossAlgo	*algo() { return _algo; }

private:
	ABossAlgo	*_algo;

  friend class Referee;
};
