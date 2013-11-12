#include			"AudioManager.h"
#include			<iostream>

bool								AudioManager::add(int id, AudioType type, bool repeat, std::string &filepath)
{
	if (type == ASOUND)
	{
		SOUND							*nS = new SOUND;

		nS->_soundBuffer = new sf::SoundBuffer;
		nS->_sound = new sf::Sound;
		if (nS->_soundBuffer->loadFromFile(filepath.c_str()))
		{
			nS->_sound->setBuffer(*(nS)->_soundBuffer);
			if (repeat == true)
				nS->_sound->setLoop(true);
			_sounds[id] = nS;
			return true;
		}
		delete nS;
		return false;
	}
	else if (type == AMUSIC)
	{
		sf::Music					*nM = new sf::Music;

		if (nM->openFromFile(filepath.c_str()))
		{
			if (repeat = true)
				nM->setLoop(true);
			_musics[id] = nM;
			return true;
		}
		delete nM;
		return false;
	}
	return false;
}

bool								AudioManager::play(int id)
{
		sounds_type::iterator			it = _sounds.find(id);

		if (it != _sounds.end() && ((*it).second->_sound->getStatus() != sf::SoundSource::Status::Playing))
		{

			(*it).second->_sound->play();
			return true;
		}

		musics_type::iterator			ot = _musics.find(id);

		if (ot != _musics.end() && ((*ot).second->getStatus() != sf::SoundSource::Status::Playing))
		{
			(*ot).second->play();
			return true;
		}
		return false;
}

bool								AudioManager::pause(int id)
{
	sounds_type::iterator			it = _sounds.find(id);

	if (it != _sounds.end())
	{
		(*it).second->_sound->pause();
		return true;
	}

	musics_type::iterator			ot = _musics.find(id);

	if (ot != _musics.end())
	{
		(*ot).second->play();
		return true;
	}
	return false;
}

bool								AudioManager::stop(int id)
{
	sounds_type::iterator			it = _sounds.find(id);

	if (it != _sounds.end())
	{
		(*it).second->_sound->stop();
		return true;
	}

	musics_type::iterator			ot = _musics.find(id);

	if (ot != _musics.end())
	{
		(*ot).second->stop();
		return true;
	}
	return false;
}