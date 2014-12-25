#pragma once

#include "Entity.h"

class AIaAlgo;

namespace game
{
  class Referee;

  class Boss : public Entity
  {
  public:
    Boss(ID id, AIaAlgo *algo);
    ~Boss(void);

    void	update(Game &game);
    void	move();
    void	fire(Game &game, bool charged);
    AIaAlgo	*algo() { return _algo; }

  private:
    AIaAlgo	*_algo;

    friend class Referee;
  };
}
