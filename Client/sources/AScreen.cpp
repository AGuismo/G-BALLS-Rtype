//
// AScreen.cpp for ascreen in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 15:45:16 2013 brigno
// Last update Thu Nov 21 01:58:52 2013 lambert kevin
//

#include	"AScreen.hh"

AScreen::AScreen(sf::RenderWindow &window, AScreen::Status status) :
  _status(status), _window(window)
{
}

AScreen::~AScreen()
{
}

AScreen::Exception::Exception(const std::string &msg) throw():
  _what(msg)
{

}

AScreen::Exception::~Exception() throw()
{

}

AScreen::Exception::Exception(const AScreen::Exception &src) throw() :
  _what(src._what)
{

}

AScreen::Exception	&AScreen::Exception::operator=(const AScreen::Exception &src) throw()
{
  if (&src != this)
    {
      this->_what = src._what;
    }
  return (*this);
}

const char		*AScreen::Exception::what() const throw()
{
  return (this->_what.c_str());
}
