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

public:
  MenuWindow(sf::RenderWindow &window, network::Manager &network);
  ~MenuWindow(void);

private:
  MenuWindow(const std::string &name);

public:
  bool					&getExit(void) const;
  bool					load();
  int					run(void);
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
  void					drawSettings(void);
  void					drawLobbyCreate(void);
  void					drawLobbyWait(int owner);
  void					drawMenuWarning();
  void					draw(void);
  int					catchEvent(void);
  int					checkAction(void);
  void					checkServer(void);
  int					checkNbPlayer(void);
  void					update(void);
  AWidget				*returnMouseFocus(float x, float y);
  static bool				removeMsgChat(const AWidget *widget);
};

#endif	/* !__MENU_WINDOW_HH__ */
