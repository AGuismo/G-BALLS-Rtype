#ifndef PLAYER_
# define	PLAYER_

# include	"AObject.h"


class Player : public AObject
{
private:
	int					_indexSprite;

public:
	void				update(Action act, LookDirection lDir, int updatedPos);
	virtual void		draw(void);

public:
	Player(ObjType obj, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow);
	~Player() {} // delete here

private:
	Player(const Player &);
	Player				operator=(const Player &);
};

#endif // !PLAYER_