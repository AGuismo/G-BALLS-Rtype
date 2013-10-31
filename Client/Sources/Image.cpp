//
// Form.cpp for Form in /home/brigno/Projects/R-Type/r-type/Client/Sources
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 19:58:14 2013 brigno
// Last update Mon Oct 28 14:57:52 2013 brigno
//

#include	"Image.hh"

Image::Image(const std::string &path, const sf::Vector2i &pos)
{
  if (!_texture.loadFromFile(path))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
  this->_image.setPosition(pos.x, pos.y);
}

Image::~Image()
{
}

const sf::Texture	&Image::getTexture() const
{
  return (this->_texture);
}

const sf::Sprite	&Image::getImage() const
{
  return (this->_image);
}

const sf::Vector2i	&Image::getPos() const
{
  return (this->_pos);
}
