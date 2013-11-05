#include "Missile.h"
#include "Player.h"

Missile::Missile(Entity &launcher, DIR dir, int pos) :
  Entity(MISSILE, pos, 1, dir, 1, 1), _launcher(launcher), _pow(1)
{
}

Missile::~Missile()
{

}
