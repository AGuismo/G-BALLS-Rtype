//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Wed Nov  6 03:09:14 2013 brigno
//

#include	"Button.hh"
#include	"Interface.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

Button::Button(const sf::Event &ev, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, AScreen::Status actionLink) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::BUTTON)
{
  sf::Vector2f posZone;

  posZone.x = posTopLeft.x;
  posZone.y = posTopLeft.y;
  this->_name = name;
  this->_image.setTexture(TextureManager::getInstance().getTexture(name)->getTexture());
  this->_image.setPosition(posZone.x, posZone.y);
  this->_actionLink = actionLink;
}

Button::~Button()
{
}

const sf::Sprite	&Button::getSprite() const
{
  return (this->_image);
}

const sf::Vector2i	&Button::getPos() const
{
  return (this->_pos);
}

AScreen::Status		Button::onFocus()
{
  this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Focus")->getTexture());
  return (this->_actionLink);
}

void			Button::stopFocus()
{
  this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name)->getTexture());
}

void			Button::onHover()
{
  this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Hover")->getTexture());
}

void			Button::stopHover()
{
  this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name)->getTexture());
}

void			Button::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}
