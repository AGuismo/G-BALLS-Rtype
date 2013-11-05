//
// TextArea.cpp for textearea in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Mon Oct 28 14:40:49 2013 brigno
// Last update Tue Nov  5 02:19:25 2013 brigno
//

#include	"TextArea.hh"
#include	"Text.hh"

TextArea::TextArea(const sf::Event &ev, const std::string &name, Text &depsText, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft,
	   const sf::Vector2i &focusBotRight) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::TEXTAREA)
{
  sf::Vector2f	posZone;

  posZone.x = posTopLeft.x;
  posZone.y = posTopLeft.y;
  if (!_texture.loadFromFile("Images/textArea.png"))
    std::cout << "Error could not load image" << std::endl;
  if (!_textureFocus.loadFromFile("Images/textAreaFocus.png"))
    std::cout << "Error could not load image" << std::endl;
  this->_name = name;
  this->_image.setTexture(_texture);
  this->_depsText = &depsText;
  this->_image.setPosition(posZone.x, posZone.y);
}

TextArea::~TextArea()
{
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

MenuWindow::Status		TextArea::onFocus()
{
  this->_depsText->onFocus();
  this->_image.setTexture(_textureFocus);
  return (MenuWindow::CONTINUE);
}

void			TextArea::stopFocus()
{
  if (this->_event.type != sf::Event::MouseButtonReleased)
    {
      this->_depsText->stopFocus();
      this->_image.setTexture(_texture);
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
