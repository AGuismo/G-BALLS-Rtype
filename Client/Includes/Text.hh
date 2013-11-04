//
// Text.hh for text in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 10:55:11 2013 brigno
// Last update Thu Oct 31 18:15:51 2013 brigno
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
  sf::Font	_font;
  sf::String	_sentence;
  sf::String	_sentencePwd;
  sf::Text	_text;
  std::string	_fontPath;
  std::size_t	_sizeLimit;

  /*AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
  /*A PUTAIN DE RETIRER !!!!!! */
  std::string	_tmpLogin;
  std::string	_tmpPwd;
  /* FIN */
  /*AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/

public:
  Text(const std::string &fontPath, const sf::Event &,
       const sf::Vector2i &topLeft, const sf::Vector2i &botRight, const size_t &size, const bool &enable);

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
  void			onFocus(void);
  void			stopFocus(void);
  void			onHover(void);
  void			stopHover(void);
  void			draw(sf::RenderWindow &);
};

#endif	/* !__TEXT_HH__ */
