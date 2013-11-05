//
// Text.cpp for test in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 11:44:54 2013 brigno
// Last update Tue Nov  5 02:19:04 2013 brigno
//

#include	"Text.hh"

Text::Text(const std::string &fontPath, const std::string &name, const sf::Event &ev, const sf::Vector2i &posTopLeft, const sf::Vector2i &focusTopLeft,
	   const sf::Vector2i &focusBotRight, const size_t &size, const bool &enable) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::TEXT)
{
  sf::Vector2f	posText;

  posText.x = posTopLeft.x;
  posText.y = posTopLeft.y;
  if (!this->_font.loadFromFile(fontPath))
    std::cerr << "Can't find path of Font file" << std::endl;
  this->_text = sf::Text(this->_sentence, this->_font, 30);
  this->_text.setColor(sf::Color(44, 127, 255));
  this->_text.move(posText);
  this->_sizeLimit = size;
  this->_enable = enable;
}

MenuWindow::Status	Text::onFocus()
{
  if (this->_event.text.unicode >= 32 && this->_event.text.unicode <= 126)
    {
      if (this->_sentenceTmp.getSize() < this->_sizeLimit)
	{
	  this->_sentence += (char)this->_event.text.unicode;
	  if (this->_enable == true)
	    this->_sentenceTmp += (char)this->_event.text.unicode;
	  else if (this->_enable == false)
	    this->_sentenceTmp += '*';
	}
    }
  else if (this->_event.text.unicode == BACKSPACE && this->_sentenceTmp.getSize())
    {
      this->_sentenceTmp.erase(this->_sentenceTmp.getSize() - 1, this->_sentenceTmp.getSize());
      this->_sentence.erase(this->_sentence.getSize() - 1, this->_sentence.getSize());
    }
  this->_tmp = this->_sentence;
  this->_text.setString(this->_sentenceTmp);
  return (MenuWindow::CONTINUE);
}

const std::string	&Text::getText() const
{
  return (this->_tmp);
}

void	Text::stopFocus()
{
}


void	Text::onHover()
{
}

void	Text::stopHover()
{
}

void	Text::draw(sf::RenderWindow &win)
{
  win.draw(this->_text);
}
