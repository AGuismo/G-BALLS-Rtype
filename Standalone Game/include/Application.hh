//
// Application.hh for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 01:50:37 2013 brigno
// Last update Sat Nov 23 18:00:08 2013 brigno
//

#ifndef		__APPLICATION_HH__
# define	__APPLICATION_HH__

# include	<iostream>
# include	<vector>
# include	<SFML/Graphics.hpp>

class		AScreen;

class		Application
{
public:
  static const int	WIDTH = 1280;
  static const int	HEIGHT = 720;
  static const char	*WINDOW_NAME;

public:
  typedef std::vector<AScreen*> screen_list;

public:
  Application();
  ~Application();
  bool	initialize();

private:
  Application(const Application &other);
  Application operator=(const Application &other);

public:
  void	run();

private:
  screen_list		_listScreen;
  sf::RenderWindow	_window;
};

#endif	/* !__APPLICATION_HH__ */
