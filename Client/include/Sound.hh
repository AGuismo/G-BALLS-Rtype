//
// Sound.hh for Sprite in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:27:10 2013 brigno
// Last update Sat Nov 23 21:14:02 2013 brigno
//

#ifndef		__SOUND_HH__
# define	__SOUND_HH__

# include       <SFML/Audio.hpp>

class Sound
{
private:
  sf::Sound		_sound;

public:
  Sound(sf::Sound sound);
  ~Sound();

private:
  Sound operator=(Sound const &other);
  Sound(Sound const &other);

public:
  sf::Sound	&getSound(void);
};

#endif	/* !__SOUND_HH__ */
