//
// TextBlock.hh for textblock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:10:46 2013 brigno
// Last update Wed Nov 20 19:59:39 2013 brigno
//

#ifndef		__LINESERVER_HH__
# define	__LINESERVER_HH__

# include	"AWidget.hh"

class		LineServer : public AWidget
{
public:
  LineServer(const std::string &name, const sf::Event &, const sf::Vector2i &posTopLeft,
	     const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, const std::string &gameName, const std::string &slotName, bool lock);
  ~LineServer(){};

private:
  LineServer(const LineServer &other);
  LineServer operator=(const LineServer &other);

private:
  sf::Vector2f			_pos;
  sf::Font			_font;
  sf::Text			_textGame;
  sf::Text			_textSlot;
  std::string			_game;
  sf::String			_tmpGame;
  sf::String			_tmpSlot;
  sf::Sprite			_image;
  bool				_lock;
  int				_focus;

public:
  const sf::Vector2f				&getPos(void) const;
  const sf::Font				&getFont(void) const;
  const sf::Text				&getTextGame(void) const;
  const sf::Text				&getTextSlot(void) const;
  const sf::String				&getTmpGame(void) const;
  const sf::String				&getTmpSlot(void) const;
  const sf::Sprite				&getImage(void) const;
  const	bool					&getLock(void) const;
  const int					&getFocus(void) const;
  MenuWindow::Status				onFocus(void);
  void						stopFocus(void);
  void						onHover(void);
  void						stopHover(void);
  void						draw(sf::RenderWindow &);
};

#endif	/* !__TEXTBLOCK_HH__ */
