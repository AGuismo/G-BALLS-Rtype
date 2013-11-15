#include "Missile.h"
#include "Player.h"

Missile::Missile(Entity &launcher, Ruint8 dir, Ruint16 pos, ID id) :
  Entity(MISSILE, pos, 1, dir, 1, 1, id), _launcher(launcher), _pow(1)
{
}

Missile::~Missile()
{

}
