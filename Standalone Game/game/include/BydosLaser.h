#ifndef BYDOSLASER_
# define	BYDOSLASER_

# include	"AObject.h"
# include	"Animation.h"

class BydosLaser : public AObject
{
private:
	Animation			_laserAnimation;

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	BydosLaser(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~BydosLaser() {}

private:
	BydosLaser(const BydosLaser &);
	BydosLaser				operator=(const BydosLaser &);
};

#endif // !BYDOSLASER_
