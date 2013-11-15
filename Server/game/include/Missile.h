#pragma once

#include "Entity.h"

class Player;
class Game;

class Missile : public Entity
{
public:
  Missile(Entity &launcher, Ruint8 dir, Ruint16 pos, ID id);
  ~Missile();
  Entity *getLauncher() const { return &_launcher;};
private:
  Entity		&_launcher;
  int			_pow;

  friend class Game;
  friend class Referee;
};
