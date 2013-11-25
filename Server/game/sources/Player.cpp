#include	"Game.h" /*Must be included in first*/
#include	"Player.h"
#include	"Missile.h"
#include	"Env.hh"

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

	for (int i = 0; i < _pos.size(); ++i)
		_prevPos[i] = _pos[i];
    if (dir == 0 || dir == 1 || dir == 7)
	  for (; it != _pos.end(); it++)
		(*it) -= rtype::Env::getInstance().game.mapSize;
    if (dir == 4 || dir == 5 || dir == 3)
      for (; it != _pos.end(); it++)
		(*it) += rtype::Env::getInstance().game.mapSize;
    if (dir == 6 || dir == 1 || dir == 5)
      for (; it != _pos.end(); it++)
		(*it) -= 1;
    if (dir == 2 || dir == 3 || dir == 7)
      for (; it != _pos.end(); it++)
		(*it) += 1;
  }

  Missile *Player::fire(Game &game, bool charged)
  {
    std::vector<game::Pos> pos;

    pos.push_back(_pos[0]);
	if (charged)
	{
		pos.push_back(_pos[0] + 1);
		return (new Missile(*this, EAST, pos, game.UniqueId(), requestCode::game::server::PLAYER_BLAST));
	}
	return (new Missile(*this, EAST, pos, game.UniqueId(), requestCode::game::server::PLAYER_LASER));
  }
}
