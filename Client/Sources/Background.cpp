//
// Background.cpp for Background in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:30:21 2013 brigno
// Last update Thu Oct 31 14:21:24 2013 brigno
//

#include	"Background.hh"

Background::Background(const std::string &path, const std::string &path2)
{
  if (!_firstTexture.loadFromFile(path))
    std::cout << "Error could not load background image" << std::endl;
  if (!_secondTexture.loadFromFile(path2))
    std::cout << "Error could not load background image" << std::endl;
  _firstBackground.setTexture(_firstTexture);
  _secondBackground.setTexture(_secondTexture);
}

Background::Background(const Background &other)
{
  this->_firstTexture = other.getFirstTexture();
  this->_secondTexture = other.getSecondTexture();
  this->_firstBackground = other.getFirstBackground();
  this->_secondBackground = other.getSecondBackground();
  this->_firstPos = other.getFirstPos();
  this->_secondPos = other.getSecondPos();
}

Background::~Background()
{
}

void		Background::scroll()
{
  _firstPos = _firstBackground.getPosition();
  _secondPos = _secondBackground.getPosition();
  if (_firstPos.x == 0)
    _secondPos.x = 1280;
  if (_firstPos.x == -1280)
    _firstPos.x = 1280;
  if (_secondPos.x == -1280)
    _secondPos.x = 1280;
  _firstPos.x -= 5;
  _secondPos.x -= 5;
  _secondBackground.setPosition(_secondPos.x, 0);
  _firstBackground.setPosition(_firstPos.x, 0);
}

const sf::Texture	&Background::getFirstTexture() const
{
  return (this->_firstTexture);
}

const sf::Texture	&Background::getSecondTexture() const
{
  return (this->_secondTexture);
}

const sf::Sprite	&Background::getFirstBackground() const
{
  return (this->_firstBackground);
}

const sf::Sprite	&Background::getSecondBackground() const
{
  return (this->_secondBackground);
}

const sf::Vector2f	&Background::getFirstPos() const
{
  return (this->_firstPos);
}

const sf::Vector2f	&Background::getSecondPos() const
{
  return (this->_secondPos);
}

void		Background::setFirstPos(float x, float y)
{
  this->_firstBackground.setPosition(x, y);
}

void		Background::setFirstPos(sf::Vector2f vector)
{
  this->_firstPos = vector;
}

void		Background::setSecondPos(float x, float y)
{
  this->_secondBackground.setPosition(x, y);
}

void		Background::setSecondPos(sf::Vector2f vector)
{
  this->_secondPos = vector;
}
