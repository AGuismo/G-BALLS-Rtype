#ifndef PLAYERLASER_
# define PLAYERLASER_

# include	"AObject.h"
# include	"Animation.h"

class PlayerLaser : public AObject
{
public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	PlayerLaser(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~PlayerLaser() {}

private:
	PlayerLaser(const PlayerLaser &);
	PlayerLaser				operator=(const PlayerLaser &);
};

#endif // !PLAYERLASER_
