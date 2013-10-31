//
// TextArea.cpp for textearea in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Mon Oct 28 14:40:49 2013 brigno
// Last update Thu Oct 31 15:58:47 2013 brigno
//

#include	"TextArea.hh"
#include	"Text.hh"

TextArea::TextArea(const sf::Event &ev, Text &depsText, const sf::Vector2i &topLeft,
	   const sf::Vector2i &botRight) :
  AWidget(ev, topLeft, botRight)
{
  sf::Vector2f	posZone;

  posZone.x = topLeft.x;
  posZone.y = topLeft.y;
  if (!_texture.loadFromFile("Images/textArea.png"))
    std::cout << "Error could not load image" << std::endl;
  this->_image.setTexture(_texture);
  this->_depsText = &depsText;
  this->_image.setPosition(posZone.x, posZone.y);
}

TextArea::~TextArea()
{
}

const int		&TextArea::getId() const
{
  return (this->_id);
}

Text			*TextArea::getDepsText()
{
  return (this->_depsText);
}

const sf::Texture	&TextArea::getTexture() const
{
  return (this->_texture);
}

const sf::Sprite	&TextArea::getSprite() const
{
  return (this->_image);
}

const sf::Vector2i	&TextArea::getPos() const
{
  return (this->_pos);
}

void			TextArea::onFocus()
{
  this->_depsText->onFocus();
  if (!_texture.loadFromFile("Images/textAreaFocus.png"))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			TextArea::stopFocus()
{
  this->_depsText->stopFocus();
  if (!_texture.loadFromFile("Images/textArea.png"))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			TextArea::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}
