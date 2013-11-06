#ifndef IOBJECT
# define IOBJECT

# include	<iostream>
# include	<SFML/Graphics.hpp>
# include	"EnumObject.h"


class IObject
{
public:
	virtual void		draw(void) = 0;
	virtual void		update(Action act) = 0;
	virtual	~IObject() {}
};

#endif // !IOBJECT