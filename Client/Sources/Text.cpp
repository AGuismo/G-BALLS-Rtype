//
// Text.cpp for test in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 11:44:54 2013 brigno
// Last update Fri Oct 25 18:07:11 2013 brigno
//

#include	<iostream>
#include	"Text.hh"

Text::Text(const std::string &fontPath, const sf::Event &ev, const sf::Vector2i &topLeft,
	   const sf::Vector2i &botRight, const size_t &size, const bool &enable, const int &id) :
  AWidget(ev, topLeft, botRight)
{
  sf::Vector2f	posText;

  posText.x = topLeft.x + 15;
  posText.y = topLeft.y + 10;
  if (!this->_font.loadFromFile(fontPath))
    std::cerr << "Can't find path of Font file" << std::endl;
  this->_text = sf::Text(this->_sentence, this->_font, 30);
  this->_text.setColor(sf::Color(44, 127, 255));
  this->_text.move(posText);
  this->_sizeLimit = size;
  this->_enable = enable;
  this->_id = id;
}

void	Text::onFocus()
{
  if (this->_event.text.unicode >= 32 && this->_event.text.unicode <= 126)
    {
      if (this->_sentence.getSize() < this->_sizeLimit)
	{
	  if (this->_enable == true)
	    this->_sentence += (char)this->_event.text.unicode;
	  else if (this->_enable == false)
	    this->_sentence += '*';
	}
    }
  else if (this->_event.text.unicode == BACKSPACE && this->_sentence.getSize())
    this->_sentence.erase(this->_sentence.getSize() - 1, this->_sentence.getSize());
  this->_text.setString(this->_sentence);
}

void	Text::draw(sf::RenderWindow &win)
{
  win.draw(this->_text);
}
