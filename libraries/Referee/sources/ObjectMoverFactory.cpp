#include			<stdexcept>

// Class from Referee
#include			"Position.hh"
#include			"Player.hh"
#include			"Missile.hh"
#include			"Mob.hh"

// Physics
#include			"ObjectMoverFactory.hh"
#include			"ObjectMover.hh"
#include			"ObjectMoverStraight.hh"

ObjectMover		*ObjectMoverFactory::createObject(const entity::Type &type, unsigned short id, const Position &pos)
{
  switch (type.desc.maj)
  {
  case entity::PLAYER:
    return (new ObjectMover(Player(id, pos, type.desc.min)));
    break;
  case entity::MISSILE:
    return (new ObjectMoverStraight(Missile(id, pos, type.desc.min)));
    break;
  case entity::MOBS:
    return (new ObjectMover(Mob(id, pos, type.desc.min)));
    break;
    //case server::SBYDOS1:
    //	return (new Bydos1(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::ZOGZOG:
    // 	return (new ZogZog(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::SLIDER:
    //	return (new Slider(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::SHRIMP_BOSS:
    //	return (new ShrimpBoss(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::GARBAGE_BOSS:
    //	return (new GarbageBoss(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::PLAYER_LASER:
    //	return (new PlayerLaser(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::PLAYER_BLAST:
    //	return (new PlayerBlast(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::BYDOS_PLASMA:
    //	return (new BydosPlasma(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::BYDOS_LASER:
    //	return (new BydosLaser(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::INDESTRUCTIBLE_WALL:
    //	return (new IndestructibleWall(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::DESTRUCTIBLE_WALL:
    //	return (new DestructibleWall(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::NORMAL_BANG:
    //	return (new Bang(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::BIG_BANG:
    //	return (new Bang(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::VITALITY_BONUS:
    //	return (new VitalityBonus(type, id, pos, ldir, text, _gameWindow));
    //	break;
    //case server::POWER_BONUS:
    //	return (new PowerBonus(type, id, pos, ldir, text, _gameWindow));
    //	break;
  default:
    throw std::runtime_error("This object doesn't exist");
    break;
  }
}

//const Animation		ObjectMoverFactory::getAnimation(const ObjectMover::type &t) const
//{
//	Animation		anim(t);
//	const game::TextureManager::texture_map_type	textures = _textureManager->getTextureByType(t);
//
//	for (game::TextureManager::texture_map_type::const_iterator it = textures.begin();
//		it != textures.end(); ++it)
//		anim.addFrame(it->first.action, it->second);
//	return (anim);
//}

ObjectMoverFactory				&ObjectMoverFactory::getInstance()
{
  static ObjectMoverFactory	factory;

  return (factory);
}

ObjectMoverFactory::ObjectMoverFactory()
{

}

ObjectMoverFactory::~ObjectMoverFactory()
{

}
