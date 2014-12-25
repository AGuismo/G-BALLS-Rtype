#ifndef ZOGZOG_
# define	ZOGZOG_

# include	"AObject.h"
# include	"Animation.h"


class ZogZog : public AObject
{
private:
	Animation			_zogZogAnimation;

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	ZogZog(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~ZogZog() {}

private:
	ZogZog(const ZogZog &);
	ZogZog				operator=(const ZogZog &);
};

#endif // !ZOGZOG_
