#pragma once

#include "Entity.h"

class Player;
class Game;

class Missile : public Entity
{
public:
	Missile(Entity &launcher, game::Dir dir, std::vector<game::Pos> &pos, game::ID id, game::Type t);
  ~Missile();

  Entity		*getLauncher() const { return &_launcher;};

private:
  Entity		&_launcher;
  int			_pow;
  game::Type	_typeMissile;

  friend class Game;
  friend class Referee;
};
