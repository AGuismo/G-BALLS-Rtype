#include	"Sound.hh"
#include	<iostream>

Sound::Sound(sf::Sound sound, sf::SoundBuffer soundBuffer):
  _sound(sound), _soundBuffer(soundBuffer)
{
}

Sound::~Sound()
{
}

const sf::Sound		&Sound::getSound() const
{
  return (this->_sound);
}

const sf::SoundBuffer	&Sound::getSoundBuffer() const
{
  return (this->_soundBuffer);
}
