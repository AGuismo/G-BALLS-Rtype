#include	"Game.h" /*Must be included in first*/
#include	"Player.h"
#include	"Missile.h"

namespace	game
{
  Player::Player(Pos pos, ID id) :
    Entity(PLAYER, pos, 1, EAST, 1, 1, id), _pow(0), _extraLife(false)
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



  void	Player::move(Dir dir)
  {
	  _prevPos = _pos;
	  if (dir == 0 || dir == 7 || dir == 1)
		  _pos -= SIZE;
	  if (dir == 4 || dir == 5 || dir == 3)
		  _pos += SIZE;
	  if (dir == 6 || dir == 7 || dir == 5)
		  _pos -= 1;
	  if (dir == 2 || dir == 3 || dir == 1)
		  _pos += 1;
  }

  Missile *Player::fire()
  {
    return (new Missile(*this, EAST, _pos, 0/*game::UniqueId()*/));
  }
}
