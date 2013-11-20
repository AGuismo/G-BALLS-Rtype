//
// Form.cpp for Form in /home/brigno/Projects/R-Type/r-type/Client/Sources
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 19:58:14 2013 brigno
// Last update Wed Nov  6 01:38:49 2013 brigno
//

#include	"Image.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

Image::Image(const std::string &name, const sf::Vector2i &pos)
{
  this->_image.setTexture(TextureManager::getInstance().getTexture(name)->getTexture());
  this->_image.setPosition(pos.x, pos.y);
}

Image::~Image()
{
}

const sf::Sprite	&Image::getImage() const
{
  return (this->_image);
}

const sf::Vector2i	&Image::getPos() const
{
  return (this->_pos);
}
