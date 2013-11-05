#ifndef PLAYER
# define	PLAYER

# include	"AObject.h"


class Player : protected AObject
{
public:
	void				draw(void);
	void				update(int newPos, Action act);

public:
	Player(ObjType obj, sf::Texture *text, int pos, sf::RenderWindow *gameWindow);
	~Player() {}

private:
	Player(const Player &);
	Player				operator=(const Player &);
};

#endif // !Player