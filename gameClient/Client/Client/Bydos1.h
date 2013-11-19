#ifndef BYDOS1
# define BYDOS1

# include	"AObject.h"
# include	"Animation.h"

class Bydos1 : public AObject
{
private:
	Animation			*_rightAnimation;
	Animation			*_leftAnimation;

public:
	void				update(Action act, LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	Bydos1(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Bydos1() {}

private:
	Bydos1(const Bydos1 &);
	Bydos1				operator=(const Bydos1 &);
};
#endif // !BYDOS1
