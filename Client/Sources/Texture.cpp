//
// Sprite.cpp for texture in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:43:53 2013 brigno
// Last update Wed Nov  6 02:15:37 2013 brigno
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
