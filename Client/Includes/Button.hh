//
// Button.hh for Button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:23:44 2013 brigno
// Last update Thu Oct 31 18:59:51 2013 brigno
//

#ifndef		__BUTTON_HH__
# define	__BUTTON_HH__

# include	"AWidget.hh"

class		Button : public AWidget
{
private:
  std::string	_path;
  std::string	_pathHover;
  std::string	_pathFocus;
  sf::Texture	_texture;
  sf::Sprite	_image;
  sf::Vector2i	_pos;

public:
  Button(const sf::Event &, const std::string &path, const std::string &pathHover, const std::string &pathFocus, const sf::Vector2i &topLeft, const sf::Vector2i &botRight);
  ~Button();

private:
  Button(const Button &other);
  Button operator=(const Button &other);

public:
  const std::string	&getPath(void) const;
  const std::string	&getPathHover(void) const;
  const std::string	&getPathFocus(void) const;
  const sf::Texture	&getTexture(void) const;
  const sf::Sprite	&getSprite(void) const;
  const sf::Vector2i	&getPos(void) const;
  void			onFocus(void);
  void			stopFocus(void);
  void			onHover(void);
  void			stopHover(void);
  void			draw(sf::RenderWindow &);
};

#endif	/* !__BUTTON_HH__ */
