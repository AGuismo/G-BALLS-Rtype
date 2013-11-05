//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Tue Nov  5 02:19:55 2013 brigno
//

#include	"Button.hh"
#include	"Interface.hh"

Button::Button(const sf::Event &ev, const std::string &name, const std::string &path, const std::string &pathHover, const std::string &pathFocus,
	       const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, MenuWindow::Status actionLink) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::BUTTON)
{
  sf::Vector2f posZone;

  posZone.x = posTopLeft.x;
  posZone.y = posTopLeft.y;
  if (!_texture.loadFromFile(path))
    std::cout << "Error could not load image" << std::endl;
  if (!_textureHover.loadFromFile(pathHover))
    std::cout << "Error could not load image" << std::endl;
  if (!_textureFocus.loadFromFile(pathFocus))
    std::cout << "Error could not load image" << std::endl;
  this->_image.setTexture(_texture);
  this->_image.setPosition(posZone.x, posZone.y);
  this->_actionLink = actionLink;
}

Button::~Button()
{
}

const sf::Texture	&Button::getTexture() const
{
  return (this->_texture);
}

const sf::Sprite	&Button::getSprite() const
{
  return (this->_image);
}

const sf::Vector2i	&Button::getPos() const
{
  return (this->_pos);
}

MenuWindow::Status		Button::onFocus()
{
  this->_image.setTexture(_textureFocus);
  return (this->_actionLink);
}

void			Button::stopFocus()
{
  this->_image.setTexture(_texture);
}

void			Button::onHover()
{
  this->_image.setTexture(_textureHover);
}

void			Button::stopHover()
{
  this->_image.setTexture(_texture);
}

void			Button::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}

