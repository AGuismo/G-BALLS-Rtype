#include	"Game.h" /*Must be included in first*/
#include	"Player.h"
#include	"Missile.h"

namespace	game
{
	Player::Player(const std::vector<game::Pos> &pos, ID id, Type t) :
		Entity(requestCode::game::server::PLAYER , pos, 1, EAST, id), _pow(0), _extraLife(false), _typePlayer(t)
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
    std::vector<game::Pos>::iterator it = _pos.begin();

    (void)dir;
    _prevPos = _pos;
    if (_dir == 0 || _dir == 1 || _dir == 7)
      for (; it != _pos.end(); it++)
	(*it) -= SIZE;
    if (_dir == 4 || _dir == 5 || _dir == 3)
      for (; it != _pos.end(); it++)
	(*it) += SIZE;
    if (_dir == 6 || _dir == 1 || _dir == 5)
      for (; it != _pos.end(); it++)
	(*it) -= 1;
    if (_dir == 2 || _dir == 3 || _dir == 7)
      for (; it != _pos.end(); it++)
	(*it) += 1;
  }

  Missile *Player::fire(Game &game, bool charged)
  {
    std::vector<game::Pos> pos;

    pos.push_back(_pos[0]);
    if (charged)
      pos.push_back(_pos[0] + 1);
	return (new Missile(*this, EAST, pos, game.UniqueId(), charged == true ? requestCode::game::server::PLAYER_BLAST : requestCode::game::server::PLAYER_LASER));
  }
}
