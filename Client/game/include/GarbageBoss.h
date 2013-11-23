#ifndef GARBAGEBOSS_
# define	GARBAGEBOSS_

# include	"AObject.h"
# include	"Animation.h"


class GarbageBoss : public AObject
{
private:
	Animation			_GarbageBossAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	GarbageBoss(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~GarbageBoss() {}

private:
	GarbageBoss(const GarbageBoss &);
	GarbageBoss				operator=(const GarbageBoss &);
};

#endif // !GARBAGEBOSS_
