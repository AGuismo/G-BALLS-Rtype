//
// TextBlock.cpp for textBlock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:25:49 2013 brigno
// Last update Wed Nov 20 20:30:14 2013 brigno
//

#include	"LineServer.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

LineServer::LineServer(const std::string &name, const sf::Event &ev, const sf::Vector2i &posTopLeft,
		       const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, const std::string &gameName, const std::string &slotName, bool lock) :
  AWidget(ev, name + gameName, posTopLeft, focusTopLeft, focusBotRight, LINESERVER)
{
  this->_pos.x = posTopLeft.x;
  this->_pos.y = posTopLeft.y;
  this->_game = gameName;
  this->_lock = lock;
  this->_focus = 0;
  if (this->_lock == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLock")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServer")->getTexture());
  if (!this->_font.loadFromFile("./Font/verdana.ttf"))
    std::cerr << "Can't find path of Font file" << std::endl;
  this->_image.setPosition(this->_pos.x, this->_pos.y);
  this->_textGame = sf::Text(this->_tmpGame, this->_font, 14);
  this->_textSlot = sf::Text(this->_tmpSlot, this->_font, 14);
  this->_tmpGame = gameName;
  this->_tmpSlot = slotName;
  this->_textGame.setColor(sf::Color(0, 0, 0));
  this->_textSlot.setColor(sf::Color(0, 0, 0));
}

const sf::Vector2f		&LineServer::getPos() const
{
  return (this->_pos);
}

const sf::Font			&LineServer::getFont() const
{
  return (this->_font);
}

const sf::Text			&LineServer::getTextGame() const
{
  return (this->_textGame);
}

const sf::Text			&LineServer::getTextSlot() const
{
  return (this->_textGame);
}

const sf::String		&LineServer::getTmpGame() const
{
  return (this->_tmpGame);
}

const sf::String		&LineServer::getTmpSlot() const
{
  return (this->_tmpSlot);
}

const sf::Sprite		&LineServer::getImage() const
{
  return (this->_image);
}

const bool			&LineServer::getLock() const
{
  return (this->_lock);
}

const int			&LineServer::getFocus() const
{
  return (this->_focus);
}

void				LineServer::draw(sf::RenderWindow &win)
{
  sf::Vector2f	posTextGame;
  sf::Vector2f	posTextSlot;

  posTextGame = this->_pos;
  posTextSlot = this->_pos;

  posTextGame.x += 10;
  posTextGame.y += 6;
  posTextSlot.x += 515;
  posTextSlot.y += 6;

  this->_textGame.setString(this->_tmpGame);
  this->_textSlot.setString(this->_tmpSlot);
  // this->_textGame.move(posTextGame.x, posTextGame.y);
  // this->_textSlot.move(posTextSlot.x, posTextGame.y);
  this->_textGame.setPosition(posTextGame.x, posTextGame.y);
  this->_textSlot.setPosition(posTextSlot.x, posTextGame.y);

  win.draw(this->_image);
  win.draw(this->_textGame);
  win.draw(this->_textSlot);
}

MenuWindow::Status		LineServer::onFocus()
{
  this->_focus = 1;
  if (this->_lock == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLockFocus")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerFocus")->getTexture());
  return (MenuWindow::SELECT_SERVER);
}

void				LineServer::stopFocus()
{
  if (this->_event.type != sf::Event::MouseButtonReleased)
    {
      this->_focus = 0;
      if (this->_lock == true)
	this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLock")->getTexture());
      else
	this->_image.setTexture(TextureManager::getInstance().getTexture("LineServer")->getTexture());
    }
}

void				LineServer::onHover()
{
}

void				LineServer::stopHover()
{
}
