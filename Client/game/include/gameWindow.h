#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>
# include	"game.h"
# include	"AScreen.hh"

namespace	network
{
  class		Manager;
}

class						GameWindow : public AScreen
{
private:
	sf::Event				_event;
	Game					_game;
	int						_width; // osef
	int						_height; //osef

public:
	bool					load(void); // check creation window + game
	int					run(void); // appelle run game =>

public:
	GameWindow(sf::RenderWindow &window, network::Manager &network);
	~GameWindow() {}

private:
	GameWindow(const GameWindow &);
	GameWindow				&operator=(const GameWindow &);
};

#endif	/* !__gameWindow_HH__ */
