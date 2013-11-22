#include			"Factory.h"
#include			"AObject.h"
#include			"TextureManager.h"
#include			"Player.h"
#include			"Bydos1.h"
#include			"PlayerLaser.h"
#include			"PlayerBlast.h"
#include			"BydosPlasma.h"
#include			"BydosLaser.h"
#include			"Bang.h"

AObject				*Factory::createObject(ObjType type, int id, int pos, LookDirection ldir)
{
	sf::Texture	*text;

	if ((text = _textureManager->getTexture(type)) != NULL)
	{
		switch (type)
		{
		case PLAYER1:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case PLAYER2:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case PLAYER3:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case PLAYER4:
			return (new Player(type, id, pos, ldir, text, _gameWindow));
			break;
		case SBYDOS1:
			return (new Bydos1(type, id, pos, ldir, text, _gameWindow));
			break;
		case PLAYER_LASER:
			return (new PlayerLaser(type, id, pos, ldir, text, _gameWindow));
			break;
		case PLAYER_BLAST:
			return (new PlayerBlast(type, id, pos, ldir, text, _gameWindow));
			break;
		case BYDOS_PLASMA:
			return (new BydosPlasma(type, id, pos, ldir, text, _gameWindow));
			break;
		case BYDOS_LASER:
			return (new BydosLaser(type, id, pos, ldir, text, _gameWindow));
			break;
		case NORMAL_BANG:
			return (new Bang(type, id, pos, ldir, text, _gameWindow));
			break;
		case BIG_BANG:
			return (new Bang(type, id, pos, ldir, text, _gameWindow));
			break;
		default:
			return NULL;
			break;
		}
	}
	return NULL;
}

Factory::Factory(sf::RenderWindow *gameWindow, game::TextureManager *TextureManager)
{
	_gameWindow = gameWindow;
	_textureManager = TextureManager;
}
