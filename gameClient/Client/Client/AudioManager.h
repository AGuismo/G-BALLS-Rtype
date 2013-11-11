#ifndef AUDIOMANAGER_
# define	AUDIOMANAGER_

#include	<cstring>
#include	<map>
#include	<SFML\Audio.hpp>



class										AudioManager
{
private:
	struct sAudio
	{
		sf::Sound							*_Audio;
		sf::SoundBuffer						*_AudioBuffer;
	};

private:
	typedef int								ID;

private:
	typedef std::map<ID, sAudio> Audios_type;
	Audios_type								_Audios;

private:
	typedef std::map<ID, sf::Music *> musics_type;
	musics_type								_musics;

public:
	bool									add(int id, std::string *Audiopath);
	bool									play(int id);
	bool									pause(int id);
	bool									stop(int id);

public:
	AudioManager() {}
	~AudioManager() {}

private:
	AudioManager(const AudioManager &);
	AudioManager					operator=(const AudioManager &);
};

#endif // !AUDIOMANAGER_
