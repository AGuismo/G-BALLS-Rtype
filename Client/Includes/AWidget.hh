//
// AWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:31:48 2013 brigno
// Last update Thu Oct 31 18:58:47 2013 brigno
//

#ifndef		__AWIDGET_HH__
# define	__AWIDGET_HH__

# include	"IWidget.hh"
# include	<iostream>
# include	<SFML/Graphics.hpp>

class			AWidget : public IWidget
{
protected:
  enum Type
    { TEXTAREA,
      TEXT,
      BUTTON
    };
protected:
  const sf::Event	&_event;
  sf::Vector2i		_topLeft;
  sf::Vector2i		_botRight;
  Type			_type;

public:
  AWidget(const sf::Event &event, const sf::Vector2i &topLeft, const sf::Vector2i &botRight, enum AWidget::Type type);
  virtual ~AWidget();
  virtual void		onFocus(void) = 0;
  virtual void		stopFocus(void) = 0;
  virtual void		onHover(void) = 0;
  virtual void		stopHover(void) = 0;
  virtual void		draw(sf::RenderWindow &) = 0;
  bool			isFocus(const sf::Vector2i &pos);
};

#endif	/* !__AWIDGET_HH__ */
