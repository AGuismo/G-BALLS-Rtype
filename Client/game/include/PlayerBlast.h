#ifndef PLAYERBLAST_
# define	PLAYERBLAST_

# include	"AObject.h"
# include	"Animation.h"

class PlayerBlast : public AObject
{
public:
	void				update(LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	PlayerBlast(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~PlayerBlast() {}

private:
	PlayerBlast(const PlayerBlast &);
	PlayerBlast				operator=(const PlayerBlast &);
};

#endif // !PLAYERBLAST_
