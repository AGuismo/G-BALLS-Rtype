//
// Sound.hh for Sprite in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:27:10 2013 brigno
// Last update Fri Nov 22 20:53:02 2013 brigno
//

#ifndef		__SOUND_HH__
# define	__SOUND_HH__

# include       <SFML/Audio.hpp>

class Sound
{
private:
  sf::Sound		_sound;
  sf::SoundBuffer	_soundBuffer;

public:
  Sound(sf::Sound sound, sf::SoundBuffer soundBuffer);
  ~Sound();

private:
  Sound operator=(Sound const &other);
  Sound(Sound const &other);

public:
  const sf::Sound	&getSound(void) const;
  const sf::SoundBuffer	&getSoundBuffer(void) const;
};

#endif	/* !__SOUND_HH__ */
