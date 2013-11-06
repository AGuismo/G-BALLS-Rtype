#pragma once

#include	<string>
#include	<iostream>
#include	<list>
#include	"Entity.h"

class Missile;
class Referee;
class Game;

namespace	game
{
  class Player : public Entity
  {
  public:
    Player(int pos);
    virtual	~Player();
    void	move(DIR dir, int speed);
    Missile	*fire();

  private:
    int		_pow;
    bool	_extraLife;

    friend class ::Referee;
    friend class ::Game;
  };
}
