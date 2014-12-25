//
// TextBlock.hh for textblock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:10:46 2013 brigno
// Last update Mon Nov 25 17:49:44 2013 brigno
//

#ifndef		__LINESERVER_HH__
# define	__LINESERVER_HH__

# include	"AWidget.hh"
# include	"GameInfo.hh"

class		LineServer : public AWidget
{
public:
  LineServer(const sf::Event &, const sf::Vector2f &posTopLeft,
	     const sf::Vector2f &focusTopLeft, const sf::Vector2f &focusBotRight,
	     const std::string &gameName, const std::string &slotName, bool lock);
  ~LineServer(){};
  LineServer &operator=(const LineServer &other);

private:
  LineServer(const LineServer &other);

private:
  sf::Vector2f			_pos;
  sf::Font			_font;
  sf::Text			_textGame;
  sf::Text			_textSlot;
  std::string			_game;
  sf::Sprite			_image;
  GameInfo			_gameInfo;
  int				_focus;

public:
  const sf::Vector2f				&getPos(void) const;
  const sf::Font				&getFont(void) const;
  const sf::Text				&getTextGame(void) const;
  const sf::Text				&getTextSlot(void) const;
  const sf::Sprite				&getImage(void) const;
  const int					&getFocus(void) const;
  const std::string				&getGame(void) const;
  const	GameInfo				&getGameInfo(void) const;
  void						setSlot(const std::string &string);
  AScreen::Status				onFocus(void);
  void						stopFocus(void);
  void						onHover(void);
  void						stopHover(void);
  void						draw(sf::RenderWindow &);
};

#endif	/* !__TEXTBLOCK_HH__ */
