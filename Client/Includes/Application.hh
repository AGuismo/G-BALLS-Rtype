//
// Application.hh for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 01:50:37 2013 brigno
// Last update Tue Nov  5 03:25:44 2013 brigno
//

#ifndef		__APPLICATION_HH__
# define	__APPLICATION_HH__

#include	<iostream>

class		Application
{
public:
  Application();
  ~Application();

public:
  Application(const Application &other);
  Application operator=(const Application &other);

public:
  void	run(const std::string &, const std::string &);
};



#endif	/* !__APPLICATION_HH__ */
