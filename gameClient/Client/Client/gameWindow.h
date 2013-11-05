#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>


class						gameWindow
{
private:
	sf::RenderWindow		_gameWindow;
	int						_width;
	int						_height;

public:
	bool					check(void); // check creation window + game
	void					run(void); // appelle run game =>

public:
	gameWindow(const std::string &name, int width, int height);
	~gameWindow() {}

private:
	gameWindow(const gameWindow &);
	gameWindow				operator=(const gameWindow &);
};

#endif	/* !__gameWindow_HH__ */
