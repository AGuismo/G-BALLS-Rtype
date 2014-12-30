//
// TextBlock.cpp for textBlock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:25:49 2013 brigno
// Last update Mon Nov 25 17:48:54 2013 brigno
//

#include	"LineServer.hh"
#include	"TextureManager.hh"
#include	"Texture.hh"

LineServer::LineServer(const sf::Event &ev, const sf::Vector2f &posTopLeft,
		       const sf::Vector2f &focusTopLeft, const sf::Vector2f &focusBotRight, const std::string &gameName, const std::string &slotName, bool lock) :
  AWidget(ev, gameName, posTopLeft, focusTopLeft, focusBotRight, LINESERVER)
{
  this->_pos = posTopLeft;
  this->_game = gameName;
  this->_focus = 0;
  this->_gameInfo._lock = lock;
  if (this->_gameInfo._lock == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLock")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServer")->getTexture());
  if (!this->_font.loadFromFile("./Font/verdana.ttf"))
    std::cerr << "Can't find path of Font file" << std::endl;
  this->_textGame = sf::Text(sf::String(this->_gameInfo._name), this->_font, 14);
  this->_textSlot = sf::Text(sf::String(this->_gameInfo._slots), this->_font, 14);
  this->_gameInfo._name = gameName;
  this->_gameInfo._slots = slotName;
  this->_gameInfo._lock = lock;
  this->_textGame.setColor(sf::Color(0, 0, 0));
  this->_textSlot.setColor(sf::Color(0, 0, 0));
}

LineServer	&LineServer::operator=(const LineServer &other)
{
  this->_pos = other.getPos();
  this->_font = other.getFont();
  this->_textGame = other.getTextGame();
  this->_textSlot = other.getTextSlot();
  this->_game = other.getGame();
  this->_image = other.getImage();
  this->_gameInfo = other.getGameInfo();
  this->_focus = other.getFocus();
  return (*this);
}

const GameInfo	&LineServer::getGameInfo() const
{
  return (this->_gameInfo);
}

void		LineServer::setSlot(const std::string &slot)
{
  this->_gameInfo._slots = slot;
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

const sf::Sprite		&LineServer::getImage() const
{
  return (this->_image);
}

const int			&LineServer::getFocus() const
{
  return (this->_focus);
}

void				LineServer::draw(sf::RenderWindow &win)
{
  _pos = this->_posTopLeft;
  this->_image.setPosition(_pos.x, _pos.y);
  this->_textGame.setPosition(_pos.x + 10, _pos.y + 6);
  this->_textSlot.setPosition(_pos.x + 515, _pos.y + 6);
  this->_textGame.setString(this->_gameInfo._name);
  this->_textSlot.setString(this->_gameInfo._slots);

  win.draw(this->_image);
  win.draw(this->_textGame);
  win.draw(this->_textSlot);
}

AScreen::Status		LineServer::onFocus()
{
  this->_focus = 1;
  if (this->_gameInfo._lock == true)
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerLockFocus")->getTexture());
  else
    this->_image.setTexture(TextureManager::getInstance().getTexture("LineServerFocus")->getTexture());
  return (AScreen::SELECT_SERVER);
}

void				LineServer::stopFocus()
{
  if (this->_event.type != sf::Event::MouseButtonReleased)
    {
        this->_focus = 0;
      if (this->_gameInfo._lock == true)
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
