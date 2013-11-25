#ifndef INDESTRUCTIBLEWALL_
# define	INDESTRUCTIBLEWALL_

# include	"AObject.h"

class IndestructibleWall : public AObject
{

public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	IndestructibleWall(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~IndestructibleWall() {}

private:
	IndestructibleWall(const IndestructibleWall &);
	IndestructibleWall				operator=(const IndestructibleWall &);
};

#endif // !INDESTRUCTIBLEWALL_
