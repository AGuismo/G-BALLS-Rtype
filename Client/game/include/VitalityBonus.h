#ifndef VITALITYBONUS_
# define VITALITYBONUS_

# include	"AObject.h"

class VitalityBonus : public AObject
{
public:
	void				update(game::Dir lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	VitalityBonus(game::Type obj, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~VitalityBonus() {}

private:
	VitalityBonus(const VitalityBonus &);
	VitalityBonus				operator=(const VitalityBonus &);
};

#endif // !VITALITYBONUS_
