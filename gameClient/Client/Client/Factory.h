#ifndef FACTORY
# define	FACTORY

#include	"EnumObject.h"

class SpriteManager;
class AObject;

namespace sf
{
	class RenderWindow;
}

class					Factory
{
private:
	sf::RenderWindow	*_gameWindow;
	SpriteManager		*_spriteManager;

public:
	AObject				*createObject(ObjType type, int id, int pos, LookDirection ld);

public:
	Factory(sf::RenderWindow *gameWindow, SpriteManager *spriteManager);
	~Factory() {}

private:
	Factory(const Factory &);
	Factory			operator=(const Factory &);
};

#endif // !FACTORY
