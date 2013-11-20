#include "Missile.h"
#include "Player.h"

Missile::Missile(Entity &launcher, game::Dir dir, std::vector<game::Pos> &pos, game::ID id) :
  Entity(game::MISSILE, pos, 1, dir, id), _launcher(launcher), _pow(1)
{
}

Missile::~Missile()
{

}
