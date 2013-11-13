#pragma once

#include "Entity.h"

class Player;
class Game;

class Missile : public Entity
{
public:
  Missile(Entity &launcher, DIR dir, int pos);
  ~Missile();
  Entity *getLauncher() const { return &_launcher;};
private:
  Entity		&_launcher;
  int			_pow;

  friend class Game;
  friend class Referee;
};
