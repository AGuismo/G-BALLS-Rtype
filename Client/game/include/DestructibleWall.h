#ifndef DESTRUCTIBLEWALL_
# define	DESTRUCTIBLEWALL_

# include	"AObject.h"

class DestructibleWall : public AObject
{
public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	DestructibleWall(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~DestructibleWall() {}

private:
	DestructibleWall(const DestructibleWall &);
	DestructibleWall				operator=(const DestructibleWall &);
};


#endif // !DESTRUCTIBLEWALL_
