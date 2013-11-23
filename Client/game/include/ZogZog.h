#ifndef ZOGZOG_
# define	ZOGZOG_

# include	"AObject.h"
# include	"Animation.h"


class ZogZog : public AObject
{
private:
	Animation			_zogZogAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	ZogZog(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~ZogZog() {}

private:
	ZogZog(const ZogZog &);
	ZogZog				operator=(const ZogZog &);
};

#endif // !ZOGZOG_
