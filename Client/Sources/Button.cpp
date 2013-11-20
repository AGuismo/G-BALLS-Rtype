//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Tue Nov 19 15:26:42 2013 brigno
//

#include	"Button.hh"
#include	"Interface.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

Button::Button(const sf::Event &ev, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, AScreen::Status actionLink, bool enable) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::BUTTON), _enable(enable)
{
  sf::Vector2f posZone;

  posZone.x = posTopLeft.x;
  posZone.y = posTopLeft.y;
  this->_name = name;
  if (this->_enable == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture(name)->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture(name + "Off")->getTexture());
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
  if (this->_enable == true)
    {
      this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Focus")->getTexture());
      return (this->_actionLink);
    }
  else
    {
      this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Off" + "Focus")->getTexture());
      return (MenuWindow::CONTINUE);
    }
}

void			Button::stopFocus()
{
  if (this->_enable == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name)->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Off")->getTexture());
}

void			Button::onHover()
{
  if (this->_enable == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Hover")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Off" + "Hover")->getTexture());
}

void			Button::stopHover()
{
  if (this->_enable == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name)->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture(this->_name + "Off")->getTexture());
}

void			Button::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}
