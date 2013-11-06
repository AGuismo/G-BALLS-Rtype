#ifndef BYDOS1
# define BYDOS1

# include	"AObject.h"

class Bydos1 : public AObject
{
public:
	void				draw(void);
	void				update(Action act);

public:
	Bydos1(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Bydos1() {}

private:
	Bydos1(const Bydos1 &);
	Bydos1				operator=(const Bydos1 &);
};



#endif // !BYDOS1
