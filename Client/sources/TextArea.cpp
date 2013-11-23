//
// TextArea.cpp for textearea in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Mon Oct 28 14:40:49 2013 brigno
// Last update Sat Nov 23 18:31:00 2013 brigno
//

#include	"TextArea.hh"
#include	"Text.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

TextArea::TextArea(const sf::Event &ev, const std::string &name, Text &depsText, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft,
	   const sf::Vector2f &focusBotRight) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::TEXTAREA)
{
  this->_name = name;
  this->_image.setTexture(TextureManager::getInstance().getTexture("TextArea")->getTexture());
  this->_depsText = &depsText;
  this->_image.setPosition(posTopLeft.x, posTopLeft.y);
}

TextArea::~TextArea()
{
}

Text			*TextArea::getDepsText()
{
  return (this->_depsText);
}

const sf::Sprite	&TextArea::getSprite() const
{
  return (this->_image);
}

const sf::Vector2f	&TextArea::getPos() const
{
  return (this->_pos);
}

AScreen::Status		TextArea::onFocus()
{
  this->_depsText->onFocus();
  this->_image.setTexture(TextureManager::getInstance().getTexture("TextAreaFocus")->getTexture());

  return (AScreen::CONTINUE);
}

void			TextArea::stopFocus()
{
  if (this->_event.type != sf::Event::MouseButtonReleased)
    {
      this->_depsText->stopFocus();
      this->_image.setTexture(TextureManager::getInstance().getTexture("TextArea")->getTexture());
    }
}

void			TextArea::onHover()
{
}

void			TextArea::stopHover()
{
}


void			TextArea::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}
