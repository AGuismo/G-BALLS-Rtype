#ifndef DESTRUCTIBLEWALL_
# define	DESTRUCTIBLEWALL_

# include	"AObject.h"

class DestructibleWall : public AObject
{
public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	DestructibleWall(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~DestructibleWall() {}

private:
	DestructibleWall(const DestructibleWall &);
	DestructibleWall				operator=(const DestructibleWall &);
};


#endif // !DESTRUCTIBLEWALL_
