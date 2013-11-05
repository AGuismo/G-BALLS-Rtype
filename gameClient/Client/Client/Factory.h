#ifndef FACTORY
# define	FACTORY

#include	"AObject.h"
#include	"EnumObject.h"

class					Factory
{
private:
	sf::RenderWindow	*_gameWindow;

public:
	AObject				createNewPoop(ObjType type, int id, int pos);

public:
	Factory(sf::RenderWindow *gameWindow);
	~Factory() {}

private:
	Factory(const Factory &);
	Factory			operator=(const Factory &);
};

#endif // !FACTORY
