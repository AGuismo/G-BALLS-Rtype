//
// Text.cpp for test in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Thu Oct 24 11:44:54 2013 brigno
// Last update Sat Nov 23 18:31:32 2013 brigno
//

#include	"Text.hh"
#include	"FontManager.hh"
#include	"Font.hh"

Text::Text(const std::string &fontName, const std::string &name, const sf::Event &ev, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft,
	   const sf::Vector2f &focusBotRight, const size_t &size, const bool &enable) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::TEXT)
{
  this->_cursor = 0;
  this->_flag = 0;

  if (name == "MsgChat")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 16);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "NameGame" || name == "PWDGame" || name == "setPWD")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "IPAddress" || name == "PortTCP" || name == "PortUDP")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "WarningMessageMenu" || name == "WarningMessageLobby")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 16);
      this->_text.setColor(sf::Color(255, 0, 0));
    }
  else if (name == "NameGameWait")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(255, 0, 0));
    }
  else
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(44, 127, 255));
    }
  this->_text.setPosition(posTopLeft.x, posTopLeft.y);
  this->_sizeLimit = size;
  this->_enable = enable;
}

Text::Text(const std::string &fontName, const std::string &name, const sf::Event &ev, const sf::Vector2f &posTopLeft, const sf::Vector2f &focusTopLeft,
	   const sf::Vector2f &focusBotRight, const size_t &size, const bool &enable, const std::string &Txt) :
  AWidget(ev, name, posTopLeft, focusTopLeft, focusBotRight, AWidget::TEXT)
{
  sf::Vector2f	posText;


  this->_flag = 0;
  posText.x = posTopLeft.x;
  posText.y = posTopLeft.y;
  this->_cursor = 0;
  if (name == "MsgChat")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 16);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "NameGame" || name == "PWDGame" || name == "setPWD")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "IPAddress" || name == "PortTCP" || name == "PortUDP")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(0, 0, 0));
    }
  else if (name == "WarningMessageMenu" || name == "WarningMessageLobby")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 16);
      this->_text.setColor(sf::Color(255, 0, 0));
    }
  else if (name == "NameGameWait")
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(255, 0, 0));
    }
  else
    {
      this->_text = sf::Text(this->_sentence, FontManager::getInstance().getFont(fontName)->getFont(), 24);
      this->_text.setColor(sf::Color(44, 127, 255));
    }
  this->_sentence = Txt;
  this->_tmp = Txt;
  this->_sentenceTmp = Txt;
  this->_text.setString(this->_sentence);
  this->_text.move(posText);
  this->_sizeLimit = size;
  this->_enable = enable;
}

void			Text::clearText()
{
  this->_cursor = 0;
  this->_sentenceTmp = "";
  this->_sentence = "";
  this->_tmp = "";
  this->_text.setString(this->_sentence);
}

Text			&Text::operator=(const Text &other)
{
  this->_enable = other.getEnable();
  this->_cursor = other.getCursor();
  this->_font = other.getFont();
  this->_sentenceTmp = other.getSentenceTmp();
  this->_sentence = other.getSentence();
  this->_tmp = other.getTmp();
  this->_text = other.getText();
  this->_fontPath = other.getFontPath();
  this->_sizeLimit = other.getSizeLimit();
  this->_flag = other.getFlag();
  return (*this);
}

AScreen::Status	Text::onFocus()
{
  if (this->_flag == 0)
    {
      this->_flag = 1;
      clearText();
    }
  if (this->_event.text.unicode >= 32 && this->_event.text.unicode <= 126)
    {
      if (this->_sentenceTmp.getSize() < this->_sizeLimit)
	{
	  this->_cursor++;
	  this->_sentence += (char)this->_event.text.unicode;
	  if (this->_enable == true)
	    this->_sentenceTmp += (char)this->_event.text.unicode;
	  else if (this->_enable == false)
	    this->_sentenceTmp += '*';
	}
    }
  else if (this->_event.text.unicode == BACKSPACE && this->_sentence.getSize() && this->_sentenceTmp.getSize())
    {
      this->_cursor--;
      this->_sentenceTmp.erase(this->_sentenceTmp.getSize() - 1, this->_sentenceTmp.getSize());
      this->_sentence.erase(this->_sentence.getSize() - 1, this->_sentence.getSize());
    }
  this->_tmp = this->_sentence;
  int startIdx = this->_cursor - 24;
  if (startIdx < 0)
    startIdx = 0;
  std::string view = this->_tmp.substr(startIdx, 24);
  if (this->_name == "MsgChat")
    this->_sentenceTmp = view;
  this->_text.setString(this->_sentenceTmp);
  return (AScreen::CONTINUE);
}

const std::string	&Text::getTmp() const
{
  return (this->_tmp);
}

const sf::Font		&Text::getFont() const
{
  return (this->_font);
}

const sf::String	&Text::getSentenceTmp() const
{
  return (this->_sentenceTmp);
}

const sf::String	&Text::getSentence() const
{
  return (this->_sentence);
}

const bool		&Text::getEnable() const
{
  return (this->_enable);
}

const int		&Text::getCursor() const
{
  return (this->_cursor);
}

const sf::Text		&Text::getText() const
{
  return (this->_text);
}

const std::string	&Text::getFontPath() const
{
  return (this->_fontPath);
}

const std::size_t	&Text::getSizeLimit() const
{
  return (this->_sizeLimit);
}

const int		&Text::getFlag() const
{
  return (this->_flag);
}

void	Text::stopFocus()
{
  this->_flag = 0;
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
