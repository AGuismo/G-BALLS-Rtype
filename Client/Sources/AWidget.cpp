//
// AWidget.cpp for Widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 16:32:14 2013 brigno
// Last update Thu Oct 31 18:58:14 2013 brigno
//

#include	"AWidget.hh"

AWidget::AWidget(const sf::Event &event, const sf::Vector2i &topLeft,
		 const sf::Vector2i &botRight, enum AWidget::Type type) :
  _event(event), _topLeft(topLeft), _botRight(botRight), _type(type)
{
}

AWidget::~AWidget()
{

}

bool	AWidget::isFocus(const sf::Vector2i &pos)
{
  return ((pos.x >= this->_topLeft.x && pos.x <= this->_botRight.x) &&
	  (pos.y >= this->_topLeft.y && pos.y <= this->_botRight.y));
}
