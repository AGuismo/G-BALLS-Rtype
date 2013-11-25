//
// AWidget.hh for widget in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 14:31:48 2013 brigno
// Last update Mon Nov 25 16:08:26 2013 brigno
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
      LINESERVER,
      BACKGROUND
    };
protected:
  const sf::Event	&_event;
  std::string		_name;
  sf::Vector2f		_posTopLeft;
  sf::Vector2f		_focusTopLeft;
  sf::Vector2f		_focusBotRight;
  Type			_type;

public:
  AWidget(const sf::Event &event, const std::string &name, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft, const sf::Vector2f &focusBotRight, enum AWidget::Type type);
  virtual ~AWidget();
  virtual AScreen::Status	onFocus(void) = 0;
  virtual void		stopFocus(void) = 0;
  virtual void		onHover(void) = 0;
  virtual void		stopHover(void) = 0;
  virtual void		draw(sf::RenderWindow &) = 0;
  virtual void		setFocus(const sf::Vector2f &, const sf::Vector2f &);
  virtual void		setPos(const sf::Vector2f &);
  bool			isFocus(const sf::Vector2f &pos);
  const std::string	&getName(void) const {return (_name);};
  const Type		&getType(void) const {return (_type);};
};

#endif	/* !__AWIDGET_HH__ */
