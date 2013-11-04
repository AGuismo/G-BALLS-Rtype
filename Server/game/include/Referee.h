#pragma once

#include	"Entity.h"

class Game;

class Referee
{
 public:
  Referee();
  ~Referee();
  void	update(Game &game);
  static bool	isCollision(Entity *a, Game &game);
 private:
  void	getIA();
  void	getBoss();
  static bool	sameCase(const Entity *a, const Entity *b);
  static bool isOnScreen(const Entity *a);

  static const int RIGHTSIDE = 42;
  static const int LEFTSIDE = -42;
  static const int TOPSIDE = -42;
  static const int BOTTOMSIDE = 42;
};
