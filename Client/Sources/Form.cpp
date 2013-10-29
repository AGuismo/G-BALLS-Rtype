//
// Form.cpp for Form in /home/brigno/Projects/R-Type/r-type/Client/Sources
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 19:58:14 2013 brigno
// Last update Thu Oct 24 17:46:05 2013 brigno
//

#include	"Form.hh"

Form::Form(const std::string &path)
{
  if (!_texture.loadFromFile(path))
    std::cout << "Error could not load background image" << std::endl;
  _form.setTexture(_texture);
}

Form::Form(const Form &other)
{
  this->_texture = other.getTexture();
  this->_form = other.getForm();
  this->_pos = other.getPos();
}

Form::~Form()
{
}

Form	Form::operator=(const Form &other)
{
  this->_texture = other.getTexture();
  this->_form = other.getForm();
  this->_pos = other.getPos();
  return (*this);
}

void	Form::setPosition()
{
  _form.setPosition(570, 330);
}

const sf::Texture	&Form::getTexture() const
{
  return (this->_texture);
}

const sf::Sprite	&Form::getForm() const
{
  return (this->_form);
}

const sf::Vector2i	&Form::getPos() const
{
  return (this->_pos);
}
