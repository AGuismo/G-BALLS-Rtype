#ifndef IOBJECT
# define IOBJECT

# include	<iostream>
# include	"EnumObject.h"


class IObject
{
public:
	virtual void					draw(void) = 0;
	virtual void					update(Action act, LookDirection lDir, int updatedPos) = 0;

public:
	virtual	~IObject() {}
};

#endif // !IOBJECT