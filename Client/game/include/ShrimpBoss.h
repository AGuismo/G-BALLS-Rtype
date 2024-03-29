#ifndef SHRIMPBOSS_
# define	SHRIMPBOSS_

# include	"AObject.h"
# include	"Animation.h"


class ShrimpBoss : public AObject
{
private:
	Animation			_ShrimpBossAnimation;

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	ShrimpBoss(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~ShrimpBoss() {}

private:
	ShrimpBoss(const ShrimpBoss &);
	ShrimpBoss				operator=(const ShrimpBoss &);
};

#endif // !SHRIMPBOSS_
