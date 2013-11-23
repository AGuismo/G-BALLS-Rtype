//
// Sprite.cpp for texture in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:43:53 2013 brigno
// Last update Sat Nov 23 10:16:05 2013 lambert kevin
//

#include	"Texture.hh"
#include	<iostream>

Texture::Texture(sf::Texture texture):
  _texture(texture)
{
}

Texture::~Texture()
{
}

const sf::Texture	&Texture::getTexture() const
{
  return (this->_texture);
}
