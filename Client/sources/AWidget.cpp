//
// AWidget.cpp for Widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 16:32:14 2013 brigno
// Last update Fri Nov 22 05:05:35 2013 brigno
//

#include	"AWidget.hh"
#include	"Interface.hh"

AWidget::AWidget(const sf::Event &event, const std::string &name, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft,
		 const sf::Vector2f &focusBotRight, enum AWidget::Type type) :
  _event(event), _posTopLeft(posTopLeft), _focusTopLeft(focusTopLeft), _focusBotRight(focusBotRight), _type(type)
{
  Interface::getInstance().addWidget(name, this);
  this->_name = name;
}

AWidget::~AWidget()
{
  Interface::getInstance().delWidget(this->_name);
}

bool	AWidget::isFocus(const sf::Vector2f &pos)
{
  return ((pos.x >= this->_focusTopLeft.x && pos.x <= this->_focusBotRight.x) &&
	  (pos.y >= this->_focusTopLeft.y && pos.y <= this->_focusBotRight.y));
}
