#ifndef SLIDER_
# define	SLIDER_

# include	"AObject.h"
# include	"Animation.h"


class Slider : public AObject
{
private:
	Animation			_leftAnimation;
	Animation			_rightAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	Slider(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Slider() {}

private:
	Slider(const Slider &);
	Slider				operator=(const Slider &);
};

#endif // !SLIDER_
