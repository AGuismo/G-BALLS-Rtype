#pragma once

#include <map>

class Referee;
class Game;
class Missile;

#define		POS_X(pos)		pos % 16
#define		POS_Y(pos)		pos / 16

enum DIR
  {
    NORTH,
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
  Entity(TYPE type, int pos, int life, DIR dir, int length, int height);
  virtual ~Entity();
  virtual void	update();
 protected:
  int				_id;
  int				_life;
  DIR				_dir;
  unsigned int		_speed;
  int				_pos;
  int				_prevPos;
  TYPE				_type;
  int				_length;
  int				_height;
  int			posX()const {return (_pos % SIZE);};
  int			posY()const {return (_pos / SIZE);};
  int			prevX()const {return (_prevPos % SIZE);};
  int			prevY()const {return (_prevPos / SIZE);};

  friend Referee;
  friend Game;
};
