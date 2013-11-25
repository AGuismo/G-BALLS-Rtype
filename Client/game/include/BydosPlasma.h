#ifndef BYDOSPLASMA_
# define	BYDOSPLASMA_

# include	"AObject.h"
# include	"Animation.h"

class BydosPlasma : public AObject
{
private:
	Animation			_plasmaAnimation;

public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	BydosPlasma(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~BydosPlasma() {}

private:
	BydosPlasma(const BydosPlasma &);
	BydosPlasma				operator=(const BydosPlasma &);
};

#endif // !BYDOSPLASMA_
