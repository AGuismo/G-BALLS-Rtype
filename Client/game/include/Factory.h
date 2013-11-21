#ifndef FACTORY
# define	FACTORY

#include	"EnumObject.h"

class TextureManager;
class AObject;

namespace sf
{
	class RenderWindow;
}

namespace	game
{
  class	TextureManager;
}

class					Factory
{
private:
	sf::RenderWindow	*_gameWindow;
	game::TextureManager	*_textureManager;

public:
	AObject				*createObject(ObjType type, int id, int pos, LookDirection ld);

public:
	Factory(sf::RenderWindow *gameWindow, game::TextureManager *TextureManager);
	~Factory() {}

private:
	Factory(const Factory &);
	Factory			operator=(const Factory &);
};

#endif // !FACTORY
