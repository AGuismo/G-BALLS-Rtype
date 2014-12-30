#ifndef PowerBonus_
# define PowerBonus_

# include	"AObject.h"

class PowerBonus : public AObject
{
public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	PowerBonus(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~PowerBonus() {}

private:
	PowerBonus(const PowerBonus &);
	PowerBonus				operator=(const PowerBonus &);
};

#endif // !PowerBonus_
