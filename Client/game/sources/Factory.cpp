#include			"Factory.h"
#include			"AObject.h"
#include			"TextureManager.h"
#include			"Player.h"
#include			"Bydos1.h"
#include			"PlayerLaser.h"
#include			"PlayerBlast.h"
#include			"BydosPlasma.h"
#include			"BydosLaser.h"
#include			"ZogZog.h"
#include			"Slider.h"
#include			"ShrimpBoss.h"
#include			"GarbageBoss.h"
#include			"Bang.h"
#include			"IndestructibleWall.h"

using namespace requestCode::game;

AObject				*Factory::createObject(game::Type type, int id, int pos, game::Dir ldir)
{
	sf::Texture	*text;

	if ((text = _textureManager->getTexture(type)) != NULL)
	{
		switch (type)
		{
		case server::PLAYER1:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::PLAYER2:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::PLAYER3:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::PLAYER4:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::SBYDOS1:
			return (new Bydos1(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::ZOGZOG:
		 	return (new ZogZog(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::SLIDER:
			return (new Slider(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::SHRIMP_BOSS:
			return (new ShrimpBoss(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::GARBAGE_BOSS:
			return (new GarbageBoss(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::PLAYER_LASER:
			return (new PlayerLaser(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::PLAYER_BLAST:
			return (new PlayerBlast(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::BYDOS_PLASMA:
			return (new BydosPlasma(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::BYDOS_LASER:
			return (new BydosLaser(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::INDESTRUCTIBLE_WALL:
			return (new IndestructibleWall(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::NORMAL_BANG:
			return (new Bang(type, id, pos, ldir, text, _gameWindow));
			break;
		case server::BIG_BANG:
			return (new Bang(type, id, pos, ldir, text, _gameWindow));
			break;
		default:
			return NULL;
			break;
		}
	}
	return NULL;
}

void				Factory::init(sf::RenderWindow *win, game::TextureManager *manager)
{
	_gameWindow = win;
	_textureManager = manager;
}

Factory				&Factory::getInstance()
{
	static Factory	factory;

	return (factory);
}

Factory::Factory():
_gameWindow(0), _textureManager(0)
{
}

Factory::~Factory()
{

}
