//
// TextBlock.hh for textblock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:10:46 2013 brigno
// Last update Tue Nov 19 23:05:46 2013 brigno
//

#ifndef		__TEXTBLOCK_HH__
# define	__TEXTBLOCK_HH__

# include	"AWidget.hh"

class		TextBlock : public AWidget
{
public:
  TextBlock(const std::string &name, const sf::Event &, const sf::Vector2i &posTopLeft,
	    const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, const size_t &size);
  ~TextBlock(){};

private:
  TextBlock(const TextBlock &other);
  TextBlock operator=(const TextBlock &other);

private:
  std::list<std::string>	_listText;
  size_t			_size;
  sf::Font			_font;
  sf::Vector2f			_pos;

public:
  const std::list<std::string>	&getListText(void) const;
  const size_t				&getSize(void) const;
  void					addText(const std::string &Msg);
  void					clearTextBlock(void);
  MenuWindow::Status			onFocus(void);
  void					stopFocus(void);
  void					onHover(void);
  void					stopHover(void);
  void					draw(sf::RenderWindow &);
};

#endif	/* !__TEXTBLOCK_HH__ */
