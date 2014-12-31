#ifndef PLAYERBLAST_
# define	PLAYERBLAST_

# include	"AObject.h"
# include	"Animation.h"

class PlayerBlast : public AObject
{
public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	PlayerBlast(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~PlayerBlast() {}

private:
	PlayerBlast(const PlayerBlast &);
	PlayerBlast				operator=(const PlayerBlast &);
};

#endif // !PLAYERBLAST_
