#include	"Font.hh"
#include	<iostream>

Font::Font(sf::Font font):
  _font(font)
{
}

Font::~Font()
{
}

const sf::Font		&Font::getFont() const
{
  return (this->_font);
}
