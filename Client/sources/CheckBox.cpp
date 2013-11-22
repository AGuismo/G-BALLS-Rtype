//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Fri Nov 22 00:18:53 2013 brigno
//

#include	"CheckBox.hh"
#include	"Interface.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

CheckBox::CheckBox(const sf::Event &ev, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, int nb, bool defaut) :
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
  if (defaut == true)
    this->onFocus();
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
  CheckBox *CheckBox1;
  CheckBox *CheckBox2;
  CheckBox *CheckBox3;
  CheckBox *CheckBox4;



  CheckBox1 = dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckOnePlayer"));
  CheckBox2 = dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckTwoPlayer"));
  CheckBox3 = dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckThreePlayer"));
  CheckBox4 = dynamic_cast<CheckBox*>(Interface::getInstance().getWidget("CheckFourPlayer"));

  if (CheckBox1 != NULL)
    {
      CheckBox1->setStates(0);
      CheckBox1->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
    }
  if (CheckBox2 != NULL)
    {
      CheckBox2->setStates(0);
      CheckBox2->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
    }
  if (CheckBox3 != NULL)
    {
      CheckBox3->setStates(0);
      CheckBox3->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
    }
  if (CheckBox4 != NULL)
    {
      CheckBox4->setStates(0);
      CheckBox4->_image.setTexture(TextureManager::getInstance().getTexture("CheckBox")->getTexture());
    }
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
