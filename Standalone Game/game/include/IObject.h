#ifndef IOBJECT
# define IOBJECT

# include	<iostream>
# include	"EnumObject.h"


class IObject
{
public:
	virtual void					draw(void) = 0;
	virtual void					update(game::Dir lDir, int updatedPos) = 0;
	virtual void					onDestruction(Game &game) = 0;

public:
	virtual	~IObject() {}
};

#endif // !IOBJECT
