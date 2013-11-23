#ifndef PLAYER_
# define	PLAYER_

# include	"AObject.h"


class Player : public AObject
{
private:
	int					_indexSprite;

public:
	void				update(LookDirection lDir, int updatedPos);
	void				draw(void);
	void				onDestruction(Game &game);

public:
	Player(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Player() {}

private:
	Player(const Player &);
	Player				operator=(const Player &);
};

#endif // !PLAYER_