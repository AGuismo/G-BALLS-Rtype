//
// TextBlock.cpp for textBlock in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov 19 21:25:49 2013 brigno
// Last update Tue Nov 19 23:56:19 2013 brigno
//

#include	"TextBlock.hh"

TextBlock::TextBlock(const std::string &name, const sf::Event &ev, const sf::Vector2i &posTopLeft,
		     const sf::Vector2i &focusTopLeft, const sf::Vector2i &focusBotRight, const size_t &size) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, TEXTBLOCK), _size(size)
{
  this->_pos.x = posTopLeft.x;
  this->_pos.y = posTopLeft.y;
  if (!this->_font.loadFromFile("./Font/verdana.ttf"))
    std::cerr << "Can't find path of Font file" << std::endl;
}

const std::list<std::string>	&TextBlock::getListText() const
{
  return (this->_listText);
}

const size_t			&TextBlock::getSize() const
{
  return (this->_size);
}

void				TextBlock::addText(const std::string &Msg)
{
  unsigned int idx = 0;

  if (this->_listText.size() > 18)
    {
      if (Msg.size() < this->_size)
	{
	  if (this->_listText.size() != 0)
	    this->_listText.pop_front();
	  this->_listText.push_back(Msg);
	}
      else
	{
	  while (idx < Msg.size())
	    {
	      std::string tmp = Msg.substr(idx, idx + this->_size);
	      if (this->_listText.size() != 0)
		this->_listText.pop_front();
	      this->_listText.push_back(tmp);
	      idx += this->_size;
	    }
	}
    }
  else
    {
      if (Msg.size() < this->_size)
	this->_listText.push_back(Msg);
      else
	{
	  while (idx < Msg.size())
	    {
	      std::string tmp = Msg.substr(idx, this->_size);

	      if (this->_listText.size() > 18)
		{
		  if (this->_listText.size() != 0)
		    this->_listText.pop_front();
		}
	      this->_listText.push_back(tmp);
	      idx += this->_size;
	    }
	}

    }
}

void				TextBlock::clearTextBlock()
{
  this->_listText.clear();
}

void				TextBlock::draw(sf::RenderWindow &win)
{
  std::list<std::string>::iterator it;
  sf::String		tmp;
  sf::Text		tmpText;
  sf::Vector2f		tmpPos;

  tmpPos = this->_pos;
  for (it = this->_listText.begin(); it != this->_listText.end(); ++it)
    {
      tmpText = sf::Text(*it, this->_font, 16);
      tmpText.setColor(sf::Color(0, 0, 0));
      tmpText.move(tmpPos.x, tmpPos.y);
      win.draw(tmpText);
      tmpPos.y += 20;
    }
}

MenuWindow::Status		TextBlock::onFocus()
{
  return (MenuWindow::CONTINUE);
}

void				TextBlock::stopFocus()
{
}

void				TextBlock::onHover()
{
}

void				TextBlock::stopHover()
{
}
