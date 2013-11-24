#ifndef		__MENU_WINDOW_HH__
# define	__MENU_WINDOW_HH__

# include	<SFML/Graphics.hpp>
# include       <SFML/Audio.hpp>
# include	<iostream>
# include	<list>
# include	"AScreen.hh"
# include	"GameInfo.hh"
# include	"ARequest.hh"
# include	"RequestCode.hh"

class		Background;
class		AWidget;
class		Image;

namespace	network
{
  class		Manager;
}

class		MenuWindow : public AScreen
{
private:
  enum States
    {
      MENU,
      MENU_ERROR,
      SETTINGS,
      LOBBY,
      LOBBY_ERROR,
      CREATE,
      WAIT,
      VERIF_PWD,
      GAME
    };

public:
  typedef std::vector<Image*>	image_list;
  typedef std::vector<AWidget*>	widget_list;
  typedef std::map<requestCode::CodeID, void (MenuWindow::*)(ARequest*)> callback_map;

private:
  image_list			_listImage;
  widget_list			_listWidget;
  callback_map			_mapCallBack;
  AWidget			*_objectFocus;
  AWidget			*_objectHover;
  GameInfo			_serverSelected;
  std::list<std::string>	_bufferChat;
  States			_currentState;
  int				_flag;
  int				_isConnected;
  sf::Music			_music;
  int				_drawBackground;
  sf::Sprite			_firstBackground;
  sf::Sprite			_secondBackground;
  sf::Vector2f			_firstPos;
  sf::Vector2f			_secondPos;

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
  void					drawMenuWarning(const std::string &Msg);
  void					drawLobbyWarning(const std::string &Msg);
  void					drawGetPWD();
  void					draw(void);
  int					catchEvent(void);
  int					checkAction(void);
  void					checkServer(void);
  int					checkNbPlayer(void);
  void					update(void);
  AWidget				*returnMouseFocus(float x, float y);
  static bool				removeMsgChat(const AWidget *widget);
  const sf::Vector2f			&getFirstPos(void) const;
  const sf::Vector2f			&getSecondPos(void) const;
  const sf::Sprite			&getFirstBackground(void) const;
  const sf::Sprite			&getSecondBackground(void) const;
  void					setFirstPos(float x, float y);
  void					setFirstPos(sf::Vector2f);
  void					setSecondPos(sf::Vector2f);
  void					setSecondPos(float x, float y);
  void					receiveSession(ARequest*);
  void					receiveOk(ARequest*);
  void					receiveForbidden(ARequest*);
  void					receiveUpdateParty(ARequest*);
  void					receiveChat(ARequest*);
  void					scroll();
};

#endif	/* !__MENU_WINDOW_HH__ */
