#ifndef PLAYER_
# define	PLAYER_

# include	"AObject.h"


class Player : public AObject
{
private:
	int					_indexSprite;

public:
	void					draw(void);
	void					update(Action act, int updatedPos);
	sf::Vector2f			*getVectorNextPos(void);
	sf::Vector2f			*getVectorCurPos(void);
	int						getCaseNextPos(void);
	int						getCaseCurPos(void);

public:
	Player(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Player() {}

private:
	Player(const Player &);
	Player				operator=(const Player &);
};

#endif // !Player_