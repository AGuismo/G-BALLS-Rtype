#ifndef BYDOSPLASMA_
# define	BYDOSPLASMA_

# include	"AObject.h"
# include	"Animation.h"

class BydosPlasma : public AObject
{
private:
	Animation			_plasmaAnimation;

public:
	void				update(LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	BydosPlasma(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~BydosPlasma() {}

private:
	BydosPlasma(const BydosPlasma &);
	BydosPlasma				operator=(const BydosPlasma &);
};

#endif // !BYDOSPLASMA_
