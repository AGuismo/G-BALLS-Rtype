#ifndef		__BUTTON_HH__
# define	__BUTTON_HH__

# include	"AWidget.hh"

class		Button : public AWidget
{
private:
  AScreen::Status	_actionLink;
  sf::Sprite	_image;
  sf::Vector2f	_pos;
  std::string	_name;
  bool		_enable;

public:
  Button(const sf::Event &, const std::string &name, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft, const sf::Vector2f &focusBotRight, AScreen::Status actionLink, bool enable);
  ~Button();

private:
  Button(const Button &other);
  Button operator=(const Button &other);

public:
  const AScreen::Status		&getActionLink(void) const;
  const sf::Sprite			&getSprite(void) const;
  const sf::Vector2f			&getPos(void) const;
  const bool				&getEnable(void) const;
  AScreen::Status			onFocus(void);
  void					stopFocus(void);
  void					onHover(void);
  void					stopHover(void);
  void					draw(sf::RenderWindow &);
};

#endif	/* !__BUTTON_HH__ */
