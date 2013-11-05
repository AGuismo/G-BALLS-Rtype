#ifndef GAME
# define	GAME

#include	<deque>
#include	<SFML/Graphics.hpp>

#include	"gameWindow.h"
#include	"SpriteManager.h"
#include	"IObject.h"

class Game
{
private:
	sf::RenderWindow			*_gameWindow;

private:
	SpriteManager				_spMan;
	std::deque<AObject>			_deqObject;

public:
	static const int			SIZE_GAME_BOARD = 16;
	static const int			PX_DEC_X = 40;
	static const int			PX_DEC_Y = 22;

public:
	static int					POSX(int x) { return (((x / SIZE_GAME_BOARD) + 1) * PX_DEC_X); } // warning 0 foireux ! motherfucker
	static int					POSY(int y) { return (((y % SIZE_GAME_BOARD) + 1) * PX_DEC_Y); }

public:
	bool						check(void);
	void						run(void);
	void						draw(void);
	void						update(void);

public:
	Game(sf::RenderWindow *gameWindow);
	~Game() {}
};

#endif // !GAME
