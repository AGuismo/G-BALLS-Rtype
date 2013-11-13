#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>
# include	"game.h"

class						gameWindow //: public AScreen
{
private:
	sf::RenderWindow		_gameWindow; // in AScreen
	sf::Event				_event;
	Game					_game;
	int						_width; // osef
	int						_height; //osef

public:
	bool					load(void); // check creation window + game
	int						run(void); // appelle run game =>

public:
	gameWindow(const std::string &name, int width, int height);
	~gameWindow() {}

private:
	gameWindow(const gameWindow &);
	gameWindow				operator=(const gameWindow &);
};

#endif	/* !__gameWindow_HH__ */
