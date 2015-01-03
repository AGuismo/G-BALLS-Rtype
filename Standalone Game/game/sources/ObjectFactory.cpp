// Class from Referee
#include			"Position.hh"
#include			"Player.hh"
#include			"Missile.hh"

// Physics
#include			"ObjectFactory.hh"
#include			"TextureManager.hh"
#include			"ObjectMover.hh"
#include			"ObjectMoverStraight.hh"

using namespace requestCode::game;

ObjectMover		*ObjectFactory::createObject(const Entity::type &type, unsigned short id, const Position &pos)
{
	switch (type.desc.maj)
	{
	case Entity::PLAYER:
		return (new ObjectMover(Player(id, pos, type.desc.min), getAnimation(type)));
		break;
	case Entity::MISSILE:
		return (new ObjectMoverStraight(Missile(id, pos, type.desc.min), getAnimation(type)));
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

const Animation		ObjectFactory::getAnimation(const Entity::type &t) const
{
	Animation		anim(t);
	const game::TextureManager::texture_map_type	textures = _textureManager->getTextureByType(t);

	for (game::TextureManager::texture_map_type::const_iterator it = textures.begin();
		it != textures.end(); ++it)
		anim.addFrame(it->first.action, it->second);
	return (anim);
}


void				ObjectFactory::init(game::TextureManager *manager)
{
	_textureManager = manager;
}

ObjectFactory				&ObjectFactory::getInstance()
{
	static ObjectFactory	factory;

	return (factory);
}

ObjectFactory::ObjectFactory():
	_textureManager(0)
{

}

ObjectFactory::~ObjectFactory()
{

}
