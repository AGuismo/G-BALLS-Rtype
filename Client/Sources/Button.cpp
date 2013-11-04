//
// Button.cpp for button in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 31 16:22:29 2013 brigno
// Last update Thu Oct 31 19:06:31 2013 brigno
//

#include	"Button.hh"

Button::Button(const sf::Event &ev, const std::string &path, const std::string &pathHover, const std::string &pathFocus, const sf::Vector2i &topLeft, const sf::Vector2i &botRight) :
  AWidget(ev, topLeft, botRight, AWidget::BUTTON)
{
  sf::Vector2f posZone;

  posZone.x = topLeft.x;
  posZone.y = topLeft.y;
  if (!_texture.loadFromFile(path))
    std::cout << "Error could not load image" << std::endl;
  this->_image.setTexture(_texture);
  this->_image.setPosition(posZone.x, posZone.y);
  this->_pathHover= pathHover;
  this->_pathFocus = pathFocus;
}

Button::~Button()
{
}

const std::string		&Button::getPath() const
{
  return (this->_path);
}

const std::string		&Button::getPathHover() const
{
  return (this->_pathHover);
}

const std::string		&Button::getPathFocus() const
{
  return (this->_pathFocus);
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

void			Button::onFocus()
{
  std::cout << "FOCUS" << this->_pathFocus << std::endl;
  if (!_texture.loadFromFile(this->_pathFocus))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			Button::stopFocus()
{
  std::cout << "STOP FOCUS" << this->_path << std::endl;
  if (!_texture.loadFromFile(this->_path))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			Button::onHover()
{
  std::cout << "HOVER" << this->_pathHover << std::endl;
  if (!_texture.loadFromFile(this->_pathHover))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			Button::stopHover()
{
  std::cout << "STOP HOVER" << this->_path << std::endl;
  if (!_texture.loadFromFile(this->_path))
    std::cout << "Error could not load background image" << std::endl;
  this->_image.setTexture(_texture);
}

void			Button::draw(sf::RenderWindow &myWin)
{
  myWin.draw(this->_image);
}

