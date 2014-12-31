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

#endif	/* !__TEXTURE_HH__ */
