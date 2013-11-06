//
// Application.hh for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 01:50:37 2013 brigno
// Last update Wed Nov  6 01:11:48 2013 brigno
//

#ifndef		__APPLICATION_HH__
# define	__APPLICATION_HH__

#include	<iostream>
#include	<vector>

class		AScreen;

class		Application
{
public:
  typedef std::vector<AScreen*> screen_list;

private:
  screen_list	_listScreen;

public:
  Application();
  ~Application();

public:
  Application(const Application &other);
  Application operator=(const Application &other);

public:
  void	run(const std::string &ip, const std::string &port);
  void	addScreen(AScreen *screen);
};

#endif	/* !__APPLICATION_HH__ */
