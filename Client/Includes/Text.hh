//
// Text.hh for text in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 10:55:11 2013 brigno
// Last update Wed Nov 20 19:45:08 2013 brigno
//

#ifndef		__TEXT_HH__
# define	__TEXT_HH__

#include	"AWidget.hh"

class		Text : public AWidget
{
public:
  static const sf::Uint32	BACKSPACE = 8;

private:
  bool		_enable;
  int		_cursor;
  sf::Font	_font;
  sf::String	_sentenceTmp;
  sf::String	_sentence;
  std::string	_tmp;
  sf::Text	_text;
  std::string	_fontPath;
  std::size_t	_sizeLimit;

public:
  Text(const std::string &fontPath, const std::string &name, const sf::Event &, const sf::Vector2i &posTopLeft,
       const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, const size_t &size, const bool &enable);

private:
  Text(const Text &other);
  Text	operator=(const Text &other);

public:
  const sf::Font	&getFont(void) const;
  const std::string	&getText(void) const;
  const int		&getId(void) const;
  const bool		&getEnable(void) const;
  const std::size_t	&getSizeLimit(void) const;
  const sf::String	&getSentence(void) const;
  const std::string	&getfontPath(void) const;
  void			clearText(void);
  MenuWindow::Status	onFocus(void);
  void			stopFocus(void);
  void			onHover(void);
  void			stopHover(void);
  void			draw(sf::RenderWindow &);
};

#endif	/* !__TEXT_HH__ */
