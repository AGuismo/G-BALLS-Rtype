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
  static bool	isOnScreen(const Entity *a);
  static bool	asAlivePlayers(Game &game);

 private:
  void	getIA();
  void	getBoss();
  static bool	sameCase(const Entity *a, const Entity *b);
  static bool	playerCollision(Entity *a, Game &game);
  static bool	iaCollision(Entity *a, Game &game);
  static bool	wallCollision(Entity *a, Game &game);
  static bool	missileCollision(Entity *a, Game &game);
  static bool	bonusCollision(Entity *a, Game &game);
  static bool	bossCollision(Entity *a, Game &game);
};
