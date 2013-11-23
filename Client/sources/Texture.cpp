#include	"Texture.hh"

Texture::Texture(sf::Texture texture):
  _texture(texture)
{
}

Texture::~Texture()
{
}

const sf::Texture	&Texture::getTexture() const
{
  return (this->_texture);
}
