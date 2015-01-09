#ifndef AUDIOMANAGER_
# define	AUDIOMANAGER_

# include	<SFML/Audio.hpp>
# include	<cstring>
# include	<map>

# include	"EnumAudio.hh"

class				AudioManager
{
private:
  struct sSound
  {
    sf::Sound			*_sound;
    sf::SoundBuffer		*_soundBuffer;

    sSound() : _sound(0), _soundBuffer(0) {};
    ~sSound() {delete _sound; delete _soundBuffer;};
  };

public:
  typedef int								ID;
  typedef sf::Music						MUSIC;
  typedef struct sSound					SOUND;

private:
  typedef std::map<ID, SOUND *>			sounds_type;
  sounds_type								_sounds;

private:
  typedef std::map<ID, MUSIC *>			musics_type;
  musics_type								_musics;

public:
  bool									add(ID, AudioType, bool repeat, const std::string &filePath);
  bool									play(ID);
  bool									pause(ID);
  bool									stop(ID);

public:
	static AudioManager					&getInstance(void);

private:
  AudioManager() {}
  ~AudioManager();

private:
  AudioManager(const AudioManager &);
  AudioManager					operator=(const AudioManager &);
};

#endif // !AUDIOMANAGER_
