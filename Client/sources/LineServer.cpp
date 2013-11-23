//
// TextBlock.cpp for textBlock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:25:49 2013 brigno
// Last update Fri Nov 22 05:05:34 2013 brigno
//

#include	"LineServer.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

LineServer::LineServer(const std::string &name, const sf::Event &ev, const sf::Vector2f &posTopLeft,
		       const sf::Vector2f &focusTopLeft, const sf::Vector2f &focusBotRight, const std::string &gameName, const std::string &slotName, bool lock) :
  AWidget(ev, name + gameName, posTopLeft, focusTopLeft, focusBotRight, LINESERVER)
{
  this->_game = gameName;
  this->_lock = lock;
  this->_focus = 0;
  if (this->_lock == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLock")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServer")->getTexture());
  if (!this->_font.loadFromFile("./Font/verdana.ttf"))
    std::cerr << "Can't find path of Font file" << std::endl;
  this->_image.setPosition(posTopLeft.x, posTopLeft.y);
  this->_textGame = sf::Text(this->_tmpGame, this->_font, 14);
  this->_textSlot = sf::Text(this->_tmpSlot, this->_font, 14);
  this->_tmpGame = gameName;
  this->_tmpSlot = slotName;
  this->_textGame.setColor(sf::Color(0, 0, 0));
  this->_textSlot.setColor(sf::Color(0, 0, 0));
  this->_textGame.setString(this->_tmpGame);
  this->_textSlot.setString(this->_tmpSlot);
  this->_textGame.setPosition(posTopLeft.x + 10, posTopLeft.y + 6);
  this->_textSlot.setPosition(posTopLeft.x + 515, posTopLeft.y + 6);


}

const std::string		&LineServer::getGame() const
{
  return (this->_game);
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
