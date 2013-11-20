//
// CheckBox.hh for checkbox in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 13:02:42 2013 brigno
// Last update Wed Nov 20 20:49:02 2013 brigno
//

#ifndef		__CHECKBOX_HH__
# define	__CHECKBOX_HH__

#include	"AWidget.hh"

class		CheckBox : public AWidget
{
  int		_states;
  sf::Sprite	_image;
  sf::Vector2i	_pos;
  std::string	_name;
  int		_nb;

public:
  CheckBox(const sf::Event &, const std::string &name, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, int nb);
  ~CheckBox();

private:
  CheckBox(const CheckBox &other);
  CheckBox operator=(const CheckBox &other);


public:
  const int		&getStates(void) const;
  const sf::Sprite	&getSprite(void) const;
  const sf::Vector2i	&getPos(void) const;
  const std::string	&getName(void) const;
  const int		&getNb(void) const;
  MenuWindow::Status	onFocus(void);
  void			clearCheck();
  void			setStates(int state);
  void			stopFocus(void);
  void			onHover(void);
  void			stopHover(void);
  void			draw(sf::RenderWindow &);
};


#endif	/* !__CHECKBOX_HH__ */
