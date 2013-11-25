#ifndef BANG_
# define BANG_

# include	"AObject.h"
# include	"Animation.h"

class Bang : public AObject
{
private:
	Animation			_bangAnimation;

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	Bang(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Bang() {}

private:
	Bang(const Bang &);
	Bang				operator=(const Bang &);
};
#endif // !BANG_
