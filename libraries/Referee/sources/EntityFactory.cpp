#include	"EntityFactory.hh"

#include	"Player.hh"
#include	"Mob.hh"
#include	"Missile.hh"

using namespace rtype::protocol;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity	*EntityFactory::createEntityByType(game::MajorType entityType) const
{
  switch (entityType)
  {
  case entity::PLAYER:
    return (new Player());
    break;
  case entity::MOBS:
    return (new Mob());
    break;
  case entity::MISSILE:
    return (new Missile());
    break;
  }
  throw IEntityFactory::WrongEntityTypeException();
}
