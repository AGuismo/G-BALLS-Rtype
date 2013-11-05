//
// Window.hh for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:31:48 2013 brigno
// Last update Tue Nov  5 03:30:33 2013 brigno
//

#ifndef		__MENU_WINDOW_HH__
# define	__MENU_WINDOW_HH__

# include	<SFML/Graphics.hpp>
# include	<iostream>

class		Background;
class		AWidget;
class		Image;
class		Network;

class		MenuWindow
{
public:
  enum Status
    {
      CONTINUE,
      EXIT,
      CHANGE_SCR
    };
public:
  typedef std::vector<Image*>	image_list;
  typedef std::vector<AWidget*>	widget_list;
private:
  Status		_status;
  sf::RenderWindow	_window;
  sf::Event		_event;
  Background		*_backgroundPtr;
  image_list		_listImage;
  widget_list		_listWidget;
  AWidget		*_objectFocus;
  AWidget		*_objectHover;
  Network		*_network;

public:
  MenuWindow(const std::string &name, int width, int height, Network *network);
  ~MenuWindow(void);

private:
  MenuWindow(const std::string &name);


public:
  bool				&getExit(void) const;
  void				run(void);
  const image_list		&getListImage(void) const;
  const widget_list		&getListWidget(void) const;
  Background			*getBackgroundPtr(void);
  const int			&getFocus(void) const;
  void				setDraw(void);
  void				draw(void);
  void				catchEvent(void);
  AWidget			*returnMouseFocus(float x, float y);
};

#endif	/* !__MENU_WINDOW_HH__ */
