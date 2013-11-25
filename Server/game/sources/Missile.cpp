#include "Missile.h"
#include "Player.h"

Missile::Missile(Entity &launcher, game::Dir dir, std::vector<game::Pos> &pos, game::ID id, game::Type t) :
Entity(requestCode::game::server::MISSILE, pos, 1, dir, id), _launcher(launcher), _pow(1), _typeMissile(t)
{
}

Missile::~Missile()
{

}

