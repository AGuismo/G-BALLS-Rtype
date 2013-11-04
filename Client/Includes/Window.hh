//
// Window.hh for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:31:48 2013 brigno
// Last update Thu Oct 31 18:05:16 2013 brigno
//

#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<SFML/Graphics.hpp>

class		Background;
class		AWidget;
class		Image;

class		Window
{
private:
  sf::RenderWindow	_window;
  sf::Event		_event;
  Background		*_backgroundPtr;
  std::vector<Image*>	_listImage;
  std::vector<AWidget*>	_listWidget;
  AWidget		*_objectFocus;

public:
  Window(const std::string &name, int width, int height);
  ~Window();

private:
  Window(const std::string &name);


public:
  void				launchWindow(void);
  const std::vector<Image*>	&getListImage(void) const;
  const std::vector<AWidget*>	&getListWidget(void) const;
  Background			*getBackgroundPtr(void);
  const int			&getFocus(void) const;
  void				setDraw(void);
  void				draw(void);
  void				catchEvent(void);
  AWidget			*returnMouseFocus(float x, float y);
};

#endif	/* !__WINDOW_HH__ */
