//
// Background.cpp for Background in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:30:21 2013 brigno
// Last update Wed Nov  6 02:14:39 2013 brigno
//

#include	"Background.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"
#include	<iostream>
Background::Background()
{
  _firstBackground.setTexture(TextureManager::getInstance().getTexture("Background1")->getTexture());
  _secondBackground.setTexture(TextureManager::getInstance().getTexture("Background2")->getTexture());
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

const sf::Vector2f	&Background::getFirstPos() const
{
  return (this->_firstPos);
}

const sf::Vector2f	&Background::getSecondPos() const
{
  return (this->_secondPos);
}

const sf::Sprite	&Background::getFirstBackground() const
{
  return (this->_firstBackground);
}

const sf::Sprite	&Background::getSecondBackground() const
{
  return (this->_secondBackground);
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
