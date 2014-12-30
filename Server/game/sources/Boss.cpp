#include "Boss.h"
#include "Missile.h"
#include "IaAlgo.hh"
#include "Player.h"

namespace game
{
  Boss::Boss(ID id, AIaAlgo *algo) :
    Entity(requestCode::game::server::BOSS, algo->pos(), algo->life(), game::WEST, id), _algo(algo)
  {
  }


  Boss::~Boss(void)
  {
    delete _algo;
  }

  void	Boss::update(Game &game)
  {
    IAPlayer	pos;
    int			i = 0;
    for (std::list<game::Client *>::iterator it = game.clients().begin(); it != game.clients().end(); ++it)
    {
      pos[i] = (*it)->player()->pos()[0];
      ++i;
    }
    int res = _algo->algo(pos);

    _dir = res;
    if (res != -1)
      move();
    fire(game, false);
  }

  void	Boss::move()
  {
    std::vector<game::Pos>::iterator it = _pos.begin();

    _prevPos = _pos;
    if (_dir == game::NORTH || _dir == game::NORTH_WEST || _dir == game::NORTH_EAST)
      for (; it != _pos.end(); it++)
	(*it) -= SIZE;
    if (_dir == game::SOUTH || _dir == game::SOUTH_WEST || _dir == game::SOUTH_EAST)
      for (; it != _pos.end(); it++)
	(*it) += SIZE;
    if (_dir == game::WEST || _dir == game::NORTH_WEST || _dir == game::SOUTH_WEST)
      for (; it != _pos.end(); it++)
	(*it) -= 1;
    if (_dir == game::EAST || _dir == game::SOUTH_EAST || _dir == game::NORTH_EAST)
      for (; it != _pos.end(); it++)
	(*it) += 1;
  }

  void	Boss::fire(Game &game, bool charged)
  {
    std::vector<game::Pos> pos;

    pos.push_back(_algo->firePos());
    if (charged)
      pos.push_back(_algo->firePos() + 1);
    while (!_algo->fires().empty())
    {
      game::Dir p = _algo->fires().back();
      game.pushMissile(new Missile(*this, p, pos, game.UniqueId(),
				   charged == true ? requestCode::game::server::BYDOS_PLASMA : requestCode::game::server::BYDOS_LASER));
      _algo->fires().pop_back();
    }
  }
}
