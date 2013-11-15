#pragma once

#include <map>
#include "game.h"

class Referee;
class Game;
class Missile;

enum DIR
  {
    NORTH = 0,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST
  };

enum TYPE
  {
    WALL,
    DESTRUCTIBLEWALL,
    MISSILE,
    IA,
    BOSS,
    PLAYER
  };

class Entity
{
protected:
  static const	int	SIZE = 16;
 public:
	 Entity(Ruint8 type, Ruint16 pos, int life, Ruint8 dir, int length, int height, ID id);
  virtual ~Entity();
  virtual void	update();
 protected:
  ID				_id;
  int				_life;
  Ruint8				_dir;
  unsigned int		_speed;
  Ruint16				_pos;
  Ruint16				_prevPos;
  Ruint8				_type;
  int				_length;
  int				_height;
  int				posX()const {return (_pos % SIZE);};
  int				posY()const {return (_pos / SIZE);};
  int				prevX()const {return (_prevPos % SIZE);};
  int				prevY()const {return (_prevPos / SIZE);};

  friend class Referee;
  friend class Game;
};
