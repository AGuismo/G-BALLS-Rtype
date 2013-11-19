#pragma once

#include	<string>
#include	<iostream>
#include	<list>
#include	"types.hh"
#include	"Entity.h"

class Missile;
class Referee;
class Game;

namespace	game
{
  class Player : public Entity
  {
  public:
    Player(Pos pos, ID id);
    virtual	~Player();

    virtual void	move(Dir dir);
    Missile	*fire(Game &game);

  private:
    int		_pow;
    bool	_extraLife;

    friend class ::Referee;
    friend class ::Game;
    friend class Client;
  };
}
