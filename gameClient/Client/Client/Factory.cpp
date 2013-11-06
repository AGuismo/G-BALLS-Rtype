#include			"Factory.h"
#include			"AObject.h"
#include			"SpriteManager.h"
#include			"Player.h"
#include			"Bydos1.h"

AObject				*Factory::createObject(ObjType type, int id, int pos, LookDirection ldir)
{
	sf::Texture	*text;

	if ((text = _spriteManager->getTexture(type)) != NULL)
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
		default:
			return NULL;
			break;
		}
	}
	return NULL;
}

Factory::Factory(sf::RenderWindow *gameWindow, SpriteManager *spriteManager)
{
	_gameWindow = gameWindow;
	_spriteManager = spriteManager;
}