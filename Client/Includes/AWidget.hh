//
// AWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:31:48 2013 brigno
// Last update Thu Oct 24 18:58:56 2013 brigno
//

#ifndef		__AWIDGET_HH__
# define	__AWIDGET_HH__

# include	"IWidget.hh"
# include	<SFML/Graphics.hpp>

class			AWidget : public IWidget
{
protected:
  const sf::Event	&_event;
  sf::Vector2i		_topLeft;
  sf::Vector2i		_botRight;

public:
  AWidget(const sf::Event &event, const sf::Vector2i &topLeft, const sf::Vector2i &botRight);
  virtual ~AWidget();
  virtual void		onFocus() = 0;
  virtual void		draw(sf::RenderWindow &) = 0;
  bool			isFocus(const sf::Vector2i &pos);
};

#endif	/* !__AWIDGET_HH__ */
