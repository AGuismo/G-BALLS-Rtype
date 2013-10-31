//
// Background.hh for Background in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:29:52 2013 brigno
// Last update Thu Oct 24 17:46:08 2013 brigno
//

#ifndef		__TITLE_HH__
# define	__TITLE_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>

class	Title
{
private:
  sf::Texture		_texture;
  sf::Sprite		_title;
  sf::Vector2i		_pos;

public:
  const sf::Texture		&getTexture(void) const;
  const sf::Sprite		&getTitle(void) const;
  const sf::Vector2i		&getPos(void) const;
  void				setPosition(void);

public:
  Title(const std::string &path);
  Title(const Title &other);
  ~Title();
  Title	operator=(const Title &other);
};

#endif	/* !__TITLE_HH__ */
