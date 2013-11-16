#pragma once

#include "Entity.h"

class Player;
class Game;

class Missile : public Entity
{
public:
  Missile(Entity &launcher, game::Dir dir, game::Pos pos, game::ID id);
  ~Missile();
  Entity *getLauncher() const { return &_launcher;};
private:
  Entity		&_launcher;
  int			_pow;

  friend class Game;
  friend class Referee;
};
