#pragma once

#include <map>
#include "Game.h"
#include "types.hh"

class Referee;
class Game;
class Missile;

namespace	game
{
  static const Dir	NORTH = 0;
  static const Dir	NORTH_EAST = 1;
  static const Dir	EAST = 2;
  static const Dir	SOUTH_EAST = 3;
  static const Dir	SOUTH = 4;
  static const Dir	SOUTH_WEST = 5;
  static const Dir	WEST = 6;
  static const Dir	NORTH_WEST = 7;
}

namespace	game
{
  static const Type WALL = 1;
  static const Type DESTRUCTIBLEWALL = 2;
  static const Type MISSILE = 3;
  static const Type IA = 4;
  static const Type BOSS = 5;
  static const Type PLAYER = 6;
}

class Entity
{
protected:
  static const	int	SIZE = 16;
public:
  Entity(game::Type type, game::Pos pos, int life, game::Dir dir, int length, int height, game::ID id);
  virtual ~Entity();
  virtual void	update();
protected:
  game::ID		_id;
  int			_life;
  game::Dir		_dir;
  unsigned int		_speed;
  game::Pos		_pos;
  game::Pos		_prevPos;
  game::Type		_type;
  int			_length;
  int			_height;
  int			posX()const {return (_pos % SIZE);};
  int			posY()const {return (_pos / SIZE);};
  int			prevX()const {return (_prevPos % SIZE);};
  int			prevY()const {return (_prevPos / SIZE);};

  friend class Referee;
  friend class Game;
};
