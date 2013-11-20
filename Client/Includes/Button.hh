//
// Button.hh for Button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:23:44 2013 brigno
// Last update Tue Nov 19 15:16:21 2013 brigno
//

#ifndef		__BUTTON_HH__
# define	__BUTTON_HH__

# include	"AWidget.hh"

class		Button : public AWidget
{
private:
  MenuWindow::Status	_actionLink;
  sf::Sprite	_image;
  sf::Vector2i	_pos;
  std::string	_name;
  bool		_enable;

public:
  Button(const sf::Event &, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, MenuWindow::Status actionLink, bool enable);
  ~Button();

private:
  Button(const Button &other);
  Button operator=(const Button &other);

public:
  const MenuWindow::Status		&getActionLink(void) const;
  const sf::Sprite			&getSprite(void) const;
  const sf::Vector2i			&getPos(void) const;
  const bool				&getEnable(void) const;
  MenuWindow::Status			onFocus(void);
  void					stopFocus(void);
  void					onHover(void);
  void					stopHover(void);
  void					draw(sf::RenderWindow &);
};

#endif	/* !__BUTTON_HH__ */
