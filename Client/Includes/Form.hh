//
// Form.hh for form in /home/brigno/Projects/R-Type/r-type/Client/Includes
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 19:56:30 2013 brigno
// Last update Thu Oct 24 17:46:06 2013 brigno
//

#ifndef		__FORM_HH__
# define	__FORM_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>

class	Form
{
private:
  sf::Texture		_texture;
  sf::Sprite		_form;
  sf::Vector2i		_pos;

public:
  const sf::Texture		&getTexture(void) const;
  const sf::Sprite		&getForm(void) const;
  const sf::Vector2i		&getPos(void) const;
  void				setPosition(void);

public:
  Form(const std::string &path);
  Form(const Form &other);
  ~Form();
  Form	operator=(const Form &other);
};

#endif	/* !__FORM_HH__ */
