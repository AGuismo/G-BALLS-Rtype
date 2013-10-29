//
// Text.hh for text in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 10:55:11 2013 brigno
// Last update Fri Oct 25 17:51:07 2013 brigno
//

#ifndef		__TEXT_HH__
# define	__TEXT_HH__

#include	"AWidget.hh"

class		Text : public AWidget
{
public:
  static const sf::Uint32	BACKSPACE = 8;

private:
  int		_id;
  bool		_enable;
  sf::Font	_font;
  sf::String	_sentence;
  sf::Text	_text;
  std::string	_fontPath;
  std::size_t	_sizeLimit;

public:
  Text(const std::string &fontPath, const sf::Event &,
       const sf::Vector2i &topLeft, const sf::Vector2i &botRight, const size_t &size, const bool &enable, const int &id);

private:
  Text(const Text &other);
  Text	operator=(const Text &other);

public:
  const sf::Font	&getFont(void) const;
  const int		&getId(void) const;
  const bool		&getEnable(void) const;
  const std::size_t	&getSizeLimit(void) const;
  const sf::String	&getSentence(void) const;
  const sf::Text	&getText(void) const;
  const std::string	&getfontPath(void) const;
  void			onFocus();
  void			draw(sf::RenderWindow &);
};

#endif	/* !__TEXT_HH__ */
