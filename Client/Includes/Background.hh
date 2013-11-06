//
// Background.hh for Background in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:29:52 2013 brigno
// Last update Wed Nov  6 01:35:28 2013 brigno
//

#ifndef		__BACKGROUND_HH__
# define	__BACKGROUND_HH__

# include	<iostream>
# include	<SFML/Graphics.hpp>

class	Background
{
private:
  sf::Sprite		_firstBackground;
  sf::Sprite		_secondBackground;
  sf::Vector2f		_firstPos;
  sf::Vector2f		_secondPos;

public:
  const sf::Vector2f		&getFirstPos(void) const;
  const sf::Vector2f		&getSecondPos(void) const;
  const sf::Sprite		&getFirstBackground(void) const;
  const sf::Sprite		&getSecondBackground(void) const;
  void				setFirstPos(float x, float y);
  void				setFirstPos(sf::Vector2f);
  void				setSecondPos(sf::Vector2f);
  void				setSecondPos(float x, float y);
  void				scroll();

public:
  Background();
  ~Background();

private:
  Background(const Background &other);
  Background	operator=(const Background &other);
};

#endif	/* !__BACKGROUND_HH__ */
