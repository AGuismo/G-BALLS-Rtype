//
// AWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:31:48 2013 brigno
// Last update Wed Nov 20 17:33:10 2013 brigno
//

#ifndef		__AWIDGET_HH__
# define	__AWIDGET_HH__

# include	"IWidget.hh"
# include	<iostream>
# include	<SFML/Graphics.hpp>

class			AWidget : public IWidget
{
public:
  enum Type
    { TEXTAREA,
      TEXT,
      BUTTON,
      CHECKBOX,
      TEXTBLOCK,
      LINESERVER
    };
protected:
  const sf::Event	&_event;
  std::string		_name;
  sf::Vector2i		_posTopLeft;
  sf::Vector2i		_focusTopLeft;
  sf::Vector2i		_focusBotRight;
  Type			_type;

public:
  AWidget(const sf::Event &event, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, enum AWidget::Type type);
  virtual ~AWidget();
  virtual MenuWindow::Status	onFocus(void) = 0;
  virtual void		stopFocus(void) = 0;
  virtual void		onHover(void) = 0;
  virtual void		stopHover(void) = 0;
  virtual void		draw(sf::RenderWindow &) = 0;
  bool			isFocus(const sf::Vector2i &pos);
  const std::string	&getName(void) const {return (_name);};
  const Type		&getType(void) const {return (_type);};
};

#endif	/* !__AWIDGET_HH__ */
