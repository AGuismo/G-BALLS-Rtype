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
	  Player(const std::vector<game::Pos> &pos, ID id);
    virtual	~Player();

    virtual void	move(Dir dir);
	Missile	*fire(Game &game, bool charged);

	void	extraLife(bool b) { _extraLife = b; };
	void	pow(int p) { _pow = p; };
	int		pow() const { return _pow; };
	void	score(game::Score p) { _score = p; };
	game::Score		score() const { return _score; };

  private:
    int		_pow;
    bool	_extraLife;
	game::Score _score;


    friend class ::Referee;
    friend class ::Game;
    friend class Client;
  };
}
