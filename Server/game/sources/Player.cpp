#include	"Player.h"
#include	"Missile.h"
#include	"Game.h"

namespace	game
{
  Player::Player(int pos) :
    Entity(PLAYER, pos, 1, EAST, 1, 1), _pow(0), _extraLife(false)
  {
#if defined(DEBUG)
    std::cout << "A new character is comming" << std::endl;
#endif
  }

  Player::~Player()
  {
#if defined(DEBUG)
    std::cout << "A player is dead" << std::endl;
#endif
  }

  void	Player::move(DIR dir, int speed)
  {
    _dir = dir;
    _speed = speed;
  }

  Missile *Player::fire()
  {
    return (new Missile(*this, EAST, _pos));
  }
}
