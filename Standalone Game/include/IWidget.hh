//
// IWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:30:15 2013 brigno
// Last update Sat Nov 23 18:20:47 2013 brigno
//

#ifndef		__IWIDGET_HH__
# define	__IWIDGET_HH__

# include	"AScreen.hh"

class		IWidget
{
public:
  virtual AScreen::Status	onFocus(void) = 0;
  virtual void	onHover(void) = 0;
  virtual void	stopHover(void) = 0;
  virtual void	stopFocus(void) = 0;
  virtual void	draw(sf::RenderWindow &) = 0;
};

#endif	/* !__IWIDGET_HH__ */
