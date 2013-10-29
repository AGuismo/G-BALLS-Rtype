//
// Window.hh for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:31:48 2013 brigno
// Last update Fri Oct 25 17:33:41 2013 brigno
//

#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<SFML/Graphics.hpp>
# include	"Background.hh"
# include	"Title.hh"
# include	"Form.hh"
# include	"Text.hh"
# include	"AWidget.hh"

class		Window
{
private:
  sf::RenderWindow	_window;
  sf::Event		_event;
  Background		*_backgroundPtr;
  Title			*_titlePtr;
  Form			*_formPtr;
  std::vector<AWidget*>	_listWidget;
  AWidget		*_objectFocus;

public:
  Window(const std::string &name, int width, int height);
  Window(const std::string &name);
  ~Window();

public:
  void			launchWindow(void);
  const std::vector<Text*>	&getListText(void) const ;
  Background		*getBackgroundPtr(void);
  Title			*getTitlePtr(void);
  Form			*getFormPtr(void);
  const int		&getFocus(void) const;
  void			setDraw(void);
  void			draw(void);
  void			catchEvent(void);
  AWidget		*returnMouseFocus(float x, float y);
};

#endif	/* !__WINDOW_HH__ */
