#ifndef PLAYER_
# define	PLAYER_

# include	"AObject.h"


class Player : public AObject
{
private:
	int					_indexSprite;
	float				_mvTime;
	sf::Clock			_mvtClock;

public:
	void				draw(void);
	void				update(Action act);

public:
	Player(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Player() {}

private:
	Player(const Player &);
	Player				operator=(const Player &);
};

#endif // !Player_