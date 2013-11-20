//
// AWidget.cpp for Widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 16:32:14 2013 brigno
// Last update Tue Nov  5 01:24:33 2013 brigno
//

#include	"AWidget.hh"
#include	"Interface.hh"

AWidget::AWidget(const sf::Event &event, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft,
		 const sf::Vector2i &focusBotRight, enum AWidget::Type type) :
  _event(event), _posTopLeft(posTopLeft), _focusTopLeft(focusTopLeft), _focusBotRight(focusBotRight), _type(type)
{
  Interface::getInstance().addWidget(name, this);
  this->_name = name;
}

AWidget::~AWidget()
{
  Interface::getInstance().delWidget(this->_name);
}

bool	AWidget::isFocus(const sf::Vector2i &pos)
{
  return ((pos.x >= this->_focusTopLeft.x && pos.x <= this->_focusBotRight.x) &&
	  (pos.y >= this->_focusTopLeft.y && pos.y <= this->_focusBotRight.y));
}
