#ifndef IOBJECT
# define IOBJECT

# include	<iostream>
# include	"EnumObject.h"


class IObject
{
public:
	virtual void		draw(void) = 0;
	virtual void		update(Action act, int updatedPos) = 0;

public:
	virtual int				getCaseNextPos(void) = 0;
	virtual int				getCaseCurPos(void) = 0;
	virtual	~IObject() {}
};

#endif // !IOBJECT