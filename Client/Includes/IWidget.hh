//
// IWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:30:15 2013 brigno
// Last update Thu Oct 24 18:59:19 2013 brigno
//

#ifndef		__IWIDGET_HH__
# define	__IWIDGET_HH__

# include	<SFML/Graphics.hpp>

class		IWidget
{
public:
  virtual void	onFocus() = 0;
  virtual void	draw(sf::RenderWindow &) = 0;
};

#endif	/* !__IWIDGET_HH__ */
