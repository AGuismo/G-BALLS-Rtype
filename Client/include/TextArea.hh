//
// TextArea.hh for Textarea in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Mon Oct 28 14:11:06 2013 brigno
// Last update Tue Nov 19 22:29:53 2013 brigno
//

#ifndef		__TEXTAREA_HH__
# define	__TEXTAREA_HH__

# include	"AWidget.hh"

class Text;

class		TextArea : public AWidget
{
private:
  std::string	_name;
  sf::Texture	_texture;
  sf::Texture	_textureFocus;
  sf::Sprite	_image;
  sf::Vector2i	_pos;
  Text		*_depsText;

public:
  TextArea(const sf::Event &, const std::string &name, Text &depsText, const sf::Vector2i &posTopLeft,
	   const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight);
  ~TextArea();

private:
  TextArea(const TextArea &other);
  TextArea operator=(const TextArea &other);

public:
  const std::string	&getName(void) const;
  const int		&getId(void) const;
  const sf::Texture	&getTexture(void) const;
  const sf::Sprite	&getSprite(void) const;
  const sf::Vector2i	&getPos(void) const;
  Text			*getDepsText(void);
  MenuWindow::Status	onFocus(void);
  void			stopFocus(void);
  void			onHover(void);
  void			stopHover(void);
  void			draw(sf::RenderWindow &);
};

#endif	/* !__TEXTAREA_HH__ */
