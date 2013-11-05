#pragma once

#include	<string>
#include	<iostream>
#include	<list>
#include	"Entity.h"
#include	"Missile.h"

class Referee;
class Game;
class Player : public Entity
{
public:
  Player(int pos);
  ~Player();
  void		move(DIR dir, int speed);
  Missile	*fire();
private:
  int		_pow;
  bool		_extraLife;

  friend Referee;
  friend Game;
};
