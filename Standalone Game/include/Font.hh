//
// Sprite.hh for Sprite in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:27:10 2013 brigno
// Last update Fri Nov 22 20:13:29 2013 brigno
//

#ifndef		__FONT_HH__
# define	__FONT_HH__

# include	<SFML/Graphics.hpp>

class Font
{
private:
  sf::Font	_font;

public:
  Font(sf::Font font);
  ~Font();

private:
  Font operator=(Font const &other);
  Font(Font const &other);

public:
  const sf::Font	&getFont(void) const;
};

#endif	/* !__SPRITE_HH__ */
