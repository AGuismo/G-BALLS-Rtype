//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Wed Nov 20 21:04:14 2013 brigno
//

#include	"CheckBox.hh"
#include	"Interface.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

CheckBox::CheckBox(const sf::Event &ev, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, int nb) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::CHECKBOX)
{
  sf::Vector2f posZone;

  posZone.x = posTopLeft.x;
  posZone.y = posTopLeft.y;
  this->_name = name;
  this->_states = 0;
  this->_nb = nb;
  this->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
  this->_image.setPosition(posZone.x, posZone.y);
}

CheckBox::~CheckBox()
{
}

const sf::Sprite	&CheckBox::getSprite() const
{
  return (this->_image);
}

const int		&CheckBox::getNb() const
{
  return (this->_nb);
}

const sf::Vector2i	&CheckBox::getPos() const
{
  return (this->_pos);
}

const std::string	&CheckBox::getName() const
{
  return (this->_name);
}

const int		&CheckBox::getStates() const
{
  return (this->_states);
}

void			CheckBox::setStates(int state)
{
  this->_states = state;
}

void			CheckBox::clearCheck()
{
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckOnePlayer"))->setStates(0);
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckTwoPlayer"))->setStates(0);
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckThreePlayer"))->setStates(0);
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckFourPlayer"))->setStates(0);
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckOnePlayer"))->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckTwoPlayer"))->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckThreePlayer"))->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
  dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckFourPlayer"))->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());

}

AScreen::Status		CheckBox::onFocus()
{
  this->clearCheck();
  this->_states = 1;
  this->_image.setTexture(TextureManager::getInstance().getTexture("CheckBoxFocus")->getTexture());
  return (MenuWindow::CONTINUE);
}

void			CheckBox::stopFocus()
{
}

void			CheckBox::onHover()
{
}

void			CheckBox::stopHover()
{
}

void			CheckBox::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}
