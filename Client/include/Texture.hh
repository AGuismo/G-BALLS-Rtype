//
// Sprite.hh for Sprite in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:27:10 2013 brigno
// Last update Wed Nov  6 01:46:41 2013 brigno
//

#ifndef		__TEXTURE_HH__
# define	__TEXTURE_HH__

# include	<SFML/Graphics.hpp>

class Texture
{
private:
  sf::Texture	_texture;

public:
  Texture(sf::Texture texture);
  ~Texture();

private:
  Texture operator=(Texture const &other);
  Texture(Texture const &other);

public:
  const sf::Texture	&getTexture(void) const;
};

#endif	/* !__SPRITE_HH__ */
