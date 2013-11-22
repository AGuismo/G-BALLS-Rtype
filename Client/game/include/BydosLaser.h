#ifndef BYDOSLASER_
# define	BYDOSLASER_
# include	"AObject.h"
# include	"Animation.h"

class BydosLaser : public AObject
{
private:
	Animation			*_laserAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	BydosLaser(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~BydosLaser() {}

private:
	BydosLaser(const BydosLaser &);
	BydosLaser				operator=(const BydosLaser &);
};

#endif // !BYDOSLASER_
