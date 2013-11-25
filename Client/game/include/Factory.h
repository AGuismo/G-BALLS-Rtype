#ifndef FACTORY
# define	FACTORY

#include	"EnumObject.h"
#include	"RequestCode.hh"

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
	AObject				*createObject(game::Type type, int id, int pos, game::Dir ld);
	void				init(sf::RenderWindow *, game::TextureManager *);

public:
	static Factory		&getInstance(void);

private:
	Factory();
	~Factory();

private:
	Factory(const Factory &);
	Factory			operator=(const Factory &);
};

#endif // !FACTORY
