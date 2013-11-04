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
  Player(int x, int y/*, udp*/);
  ~Player();
  void	move(DIR dir, int speed);
  Missile	*fire();
 private:
  int			_pow;
  bool			_extraLife;
  //ClientAccepted *	_udp;

  friend Referee;
  friend Game;
};
