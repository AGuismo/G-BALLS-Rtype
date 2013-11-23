#include	"MediaAudioManager.hh"
#include	"Sound.hh"

MediaAudioManager::MediaAudioManager()
{
}

MediaAudioManager::~MediaAudioManager()
{

}

MediaAudioManager	&MediaAudioManager::getInstance()
{
  static MediaAudioManager	*singleton = 0;

  if (singleton == 0)
    singleton = new MediaAudioManager;
  return (*singleton);
}

void			MediaAudioManager::addSound(const std::string &key, Sound *value)
{
  _lnkSound[key] = value;
}

void			MediaAudioManager::addSound(const std::string &key, const std::string &path)
{
  Sound	*tmp;
  sf::Sound sound;
  sf::SoundBuffer soundBuffer;

  if (soundBuffer.loadFromFile(path))
    throw Exception("Failed to load sound location: " + path);
  sound.setBuffer(soundBuffer);
  sound.setLoop(false);
  tmp = new Sound(sound, soundBuffer);
  addSound(key, tmp);
}

void			MediaAudioManager::delSound(const std::string &key)
{
  _lnkSound.erase(key);
}

Sound			*MediaAudioManager::getSound(const std::string &key)
{
  Sound_type::iterator	it = _lnkSound.find(key);

  if (it == _lnkSound.end())
    return 0;
  return (it->second);
}

MediaAudioManager::Exception::Exception(const std::string &msg) throw():
  _what(msg)
{

}

MediaAudioManager::Exception::~Exception() throw()
{

}

MediaAudioManager::Exception::Exception(const MediaAudioManager::Exception &src) throw() :
  _what(src._what)
{

}

MediaAudioManager::Exception	&MediaAudioManager::Exception::operator=(const MediaAudioManager::Exception &src) throw()
{
  if (&src != this)
    {
      this->_what = src._what;
    }
  return (*this);
}

const char		*MediaAudioManager::Exception::what() const throw()
{
  return (this->_what.c_str());
}
