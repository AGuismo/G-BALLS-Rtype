//
// Title.cpp for title in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 18:04:35 2013 brigno
// Last update Thu Oct 24 17:46:06 2013 brigno
//

#include	"Title.hh"

Title::Title(const std::string &path)
{
  if (!_texture.loadFromFile(path))
    std::cout << "Error could not load background image" << std::endl;
  _title.setTexture(_texture);
}

Title::Title(const Title &other)
{
  this->_texture = other.getTexture();
  this->_title = other.getTitle();
  this->_pos = other.getPos();
}

Title::~Title()
{
}

Title	Title::operator=(const Title &other)
{
  this->_texture = other.getTexture();
  this->_title = other.getTitle();
  this->_pos = other.getPos();
  return (*this);
}

void	Title::setPosition()
{
  _title.setPosition(400, 100);
}

const sf::Texture	&Title::getTexture() const
{
  return (this->_texture);
}

const sf::Sprite	&Title::getTitle() const
{
  return (this->_title);
}

const sf::Vector2i	&Title::getPos() const
{
  return (this->_pos);
}
