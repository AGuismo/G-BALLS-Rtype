#ifndef BANG_
# define BANG_

# include	"AObject.h"
# include	"Animation.h"

class Bang : public AObject
{
private:
	Animation			_bangAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	Bang(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Bang() {}

private:
	Bang(const Bang &);
	Bang				operator=(const Bang &);
};
#endif // !BANG_
