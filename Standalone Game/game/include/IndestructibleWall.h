#ifndef INDESTRUCTIBLEWALL_
# define	INDESTRUCTIBLEWALL_

# include	"AObject.h"

class IndestructibleWall : public AObject
{

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	IndestructibleWall(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~IndestructibleWall() {}

private:
	IndestructibleWall(const IndestructibleWall &);
	IndestructibleWall				operator=(const IndestructibleWall &);
};

#endif // !INDESTRUCTIBLEWALL_
