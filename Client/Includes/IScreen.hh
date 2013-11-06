//
// Screen.hh for Screen in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 15:00:31 2013 brigno
// Last update Wed Nov  6 01:46:05 2013 brigno
//

#ifndef		__ISCREEN_HH__
# define	__ISCREEN_HH__

# include	<SFML/Graphics.hpp>

class		IScreen
{
public:
  virtual int run(void) = 0;
};

#endif	/* !__ISCREEN_HH__ */
