//
// Window.hh for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:31:48 2013 brigno
// Last update Wed Nov  6 01:26:31 2013 brigno
//

#ifndef		__MENU_WINDOW_HH__
# define	__MENU_WINDOW_HH__

# include	<SFML/Graphics.hpp>
# include	<iostream>
# include	"AScreen.hh"

class		Background;
class		AWidget;
class		Image;
class		Network;

class		MenuWindow : public AScreen
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
  Background		*_backgroundPtr;
  image_list		_listImage;
  widget_list		_listWidget;
  AWidget		*_objectFocus;
  AWidget		*_objectHover;

public:
  MenuWindow(const std::string &name, int width, int height, Network *network);
  ~MenuWindow(void);

private:
  MenuWindow(const std::string &name);

public:
  bool				&getExit(void) const;
  int				run(void);
  void				setListSprite(sf::Sprite);
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
