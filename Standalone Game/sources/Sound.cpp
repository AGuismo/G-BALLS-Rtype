#include	"Sound.hh"
#include	<iostream>

Sound::Sound(sf::Sound sound):
  _sound(sound)
{
}

Sound::~Sound()
{
}

sf::Sound		&Sound::getSound()
{
  return (this->_sound);
}
