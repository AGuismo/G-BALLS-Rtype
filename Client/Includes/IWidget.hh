//
// IWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:30:15 2013 brigno
// Last update Tue Nov  5 02:13:45 2013 brigno
//

#ifndef		__IWIDGET_HH__
# define	__IWIDGET_HH__

# include	"MenuWindow.hh"

class MenuWindow;

class		IWidget
{
public:
  virtual MenuWindow::Status	onFocus(void) = 0;
  virtual void	onHover(void) = 0;
  virtual void	stopHover(void) = 0;
  virtual void	stopFocus(void) = 0;
  virtual void	draw(sf::RenderWindow &) = 0;
};

#endif	/* !__IWIDGET_HH__ */
