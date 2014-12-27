#pragma once

#include <map>
#include "Game.hh"
#include "types.hh"


namespace	game
{
  class Referee;
  class Game;
  class Missile;


  static const Dir	NORTH = 0;
  static const Dir	NORTH_EAST = 1;
  static const Dir	EAST = 2;
  static const Dir	SOUTH_EAST = 3;
  static const Dir	SOUTH = 4;
  static const Dir	SOUTH_WEST = 5;
  static const Dir	WEST = 6;
  static const Dir	NORTH_WEST = 7;

  class Entity
  {
  protected:
    static const	int	SIZE = 16;
  public:
    Entity(game::Type type, std::vector<game::Pos> pos, int life, game::Dir dir, game::ID id);
    virtual ~Entity();
    virtual void	update();

  public:
    game::ID		&id();
    game::Dir		&dir();
    std::vector<game::Pos>	&pos();
    game::Type		&type();
  protected:
    game::ID		_id;
    int			_life;
    game::Dir		_dir;
    unsigned int	_speed;
    std::vector<game::Pos>	_pos;
    std::vector<game::Pos>	_prevPos;
    game::Type	_type;

    friend class Referee;
    friend class Game;
  };
}
