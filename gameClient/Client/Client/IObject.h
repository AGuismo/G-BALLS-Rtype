#ifndef IOBJECT
# define IOBJECT

# include	<iostream>
# include	"EnumObject.h"


class IObject
{
public:
	virtual void					draw(void) = 0;
	virtual void					update(Action act, int updatedPos) = 0;

public:
	virtual const sf::Vector2f		*getVectorNextPos(void) = 0;
	virtual const sf::Vector2f		*getVectorCurPos(void) = 0;
	virtual const int				getCaseNextPos(void) = 0;
	virtual const int				getCaseCurPos(void) = 0;
	virtual	~IObject() {}
};

#endif // !IOBJECT