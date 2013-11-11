#include			"SoundManager.h"
#include			<iostream>

bool								SoundManager::addSound(int id, std::string *soundpath)
{
	sf::SoundBuffer					*sBuff = new sf::SoundBuffer;

	if (sBuff->loadFromFile(soundpath->c_str()))
	{
		_sounds[id] = new sf::SoundBuffer;
		_sounds[id]->loadFromFile(soundpath->c_str());
		return true;
	}
	return false;
}

bool								SoundManager::playSound(int id)
{
	sf::Sound						sS;
	sounds_type::iterator			it = _sounds.find(id);

	if (it != _sounds.end())
	{
		std::cout << "LA OK" << std::endl;
		sS.setBuffer(*(it)->second);
		sS.play();
		return true;
	}
	return false;
}

bool								SoundManager::pauseSound(int id)
{
	sf::Sound						sS;
	sounds_type::iterator			it = _sounds.find(id);

	if (it != _sounds.end())
	{
		sS.setBuffer(*(it)->second);
		sS.pause();
		return true;
	}
	return false;
}

bool								SoundManager::stopSound(int id)
{
	sf::Sound						sS;
	sounds_type::iterator			it = _sounds.find(id);

	if (it != _sounds.end())
	{
		sS.setBuffer(*(it)->second);
		sS.stop();
		return true;
	}
	return false;
}
