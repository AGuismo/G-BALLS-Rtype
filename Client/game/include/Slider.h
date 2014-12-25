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
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	Slider(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Slider() {}

private:
	Slider(const Slider &);
	Slider				operator=(const Slider &);
};

#endif // !SLIDER_
