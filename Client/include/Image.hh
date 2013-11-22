//
// Form.hh for form in /home/brigno/Projects/R-Type/r-type/Client/Includes
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 19:56:30 2013 brigno
// Last update Fri Nov 22 05:05:33 2013 brigno
//

#ifndef		__IMAGE_HH__
# define	__IMAGE_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>

class	Image
{
private:
  sf::Sprite		_image;
  sf::Vector2f		_pos;

public:
  const sf::Sprite		&getImage(void) const;
  const sf::Vector2f		&getPos(void) const;

public:
  Image(const std::string &name, const sf::Vector2f &pos);
  ~Image();

private:
  Image(const Image &);
  Image	operator=(const Image &);
};

#endif	/* !__IMAGE_HH__ */
