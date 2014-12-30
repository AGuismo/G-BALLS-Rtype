#pragma once

#include	<string>
#include	<iostream>
#include	<list>
#include	"types.hh"
#include	"Entity.h"


namespace	game
{
  class Missile;
  class Referee;
  class Game;

  class Player : public Entity
  {
  public:
    Player(const std::vector<game::Pos> &pos, ID id, Type t);
    virtual	~Player();

    virtual void	move(Dir dir);
    Missile	*fire(Game &game, bool charged);

    void	extraLife(bool b) { _extraLife = b; };
    void	pow(int p) { _pow = p; };
    int		pow() const { return _pow; };
    Type	typePlayer() const{ return _type; };

  private:
    int		_pow;
    bool	_extraLife;
    Type	_typePlayer;


    friend class Referee;
    friend class Game;
    friend class Client;
  };
}
