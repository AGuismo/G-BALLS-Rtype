//
// AScreen.cpp for ascreen in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 15:45:16 2013 brigno
// Last update Wed Nov  6 03:13:30 2013 brigno
//

#include	"AScreen.hh"

AScreen::AScreen(const std::string &name, int width, int height, Network *network, AScreen::Status status)
{
  this->_window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
  this->_network = network;
  this->_status = status;
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
