#ifndef BYDOS1
# define BYDOS1

# include	"AObject.h"
# include	"Animation.h"

class Bydos1 : public AObject
{
private:
	Animation			_leftAnimation;
	Animation			_rightAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	Bydos1(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Bydos1() {}

private:
	Bydos1(const Bydos1 &);
	Bydos1				operator=(const Bydos1 &);
};

#endif // !BYDOS1
