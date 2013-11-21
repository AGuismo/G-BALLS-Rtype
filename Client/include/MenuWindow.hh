//
// Window.hh for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:31:48 2013 brigno
// Last update Thu Nov 21 01:45:06 2013 lambert kevin
//

#ifndef		__MENU_WINDOW_HH__
# define	__MENU_WINDOW_HH__

# include	<SFML/Graphics.hpp>
# include	<iostream>
# include	<list>
# include	"AScreen.hh"

class		Background;
class		AWidget;
class		Image;
namespace	network
{
  class		Manager;
}

class		MenuWindow : public AScreen
{
public:
  typedef std::vector<Image*>	image_list;
  typedef std::vector<AWidget*>	widget_list;

private:
  Background			*_backgroundPtr;
  image_list			_listImage;
  widget_list			_listWidget;
  AWidget			*_objectFocus;
  AWidget			*_objectHover;
  std::list<std::string>	_bufferChat;
  int				_flag;
  network::Manager		&_network;

public:
  MenuWindow(sf::RenderWindow &window, network::Manager &network);
  ~MenuWindow(void);

private:
  MenuWindow(const std::string &name);

public:
  bool					&getExit(void) const;
  bool					load();
  void					run(void);
  void					setListSprite(sf::Sprite);
  const image_list			&getListImage(void) const;
  const widget_list			&getListWidget(void) const;
  Background				*getBackgroundPtr(void);
  const int				&getFocus(void) const;
  const std::vector<std::string>	&getBufferChat(void) const;
  void					tmp(const std::string &Msg);
  void					clearWindow(void);
  void					setDraw(void);
  void					drawMenu(void);
  void					drawLobby(void);
  void					removeWidget(const std::string &other);
  void					drawLobbyCreate(void);
  void					drawLobbyWait(int owner);
  void					draw(void);
  void					catchEvent(void);
  void					checkAction(void);
  void					checkServer(void);
  int					checkNbPlayer(void);
  void					update(void);
  AWidget				*returnMouseFocus(float x, float y);
  static bool				removeMsgChat(const AWidget *widget);
};

#endif	/* !__MENU_WINDOW_HH__ */
