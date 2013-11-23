//
// TextureManager.cpp for texturemanager in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:24:09 2013 brigno
// Last update Sat Nov 23 10:20:05 2013 lambert kevin
//

// #include	<windows.h>
#include	"TextureManager.hh"
#include	"Texture.hh"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
  for (Texture_type::iterator it = _lnk.begin(); it != _lnk.end(); ++it)
    delete it->second;
  _lnk.clear();
}

TextureManager	&TextureManager::getInstance()
{
  static TextureManager	singleton;

  return (singleton);
}

void			TextureManager::addTexture(const std::string &key, Texture *value)
{
  _lnk[key] = value;
}

void			TextureManager::addTexture(const std::string &key, const std::string &path)
{
  sf::Texture	texture;
  Texture	*tmp;

  if (!texture.loadFromFile(path))
	  throw Exception("Failed to load sprite location: " + path);
  tmp = new Texture(texture);
  addTexture(key, tmp);
}

void			TextureManager::delTexture(const std::string &key)
{
  _lnk.erase(key);
}

Texture			*TextureManager::getTexture(const std::string &key)
{
  Texture_type::iterator	it = _lnk.find(key);

  if (it == _lnk.end())
    return 0;
  return (it->second);
}

TextureManager::Exception::Exception(const std::string &msg) throw():
  _what(msg)
{

}

TextureManager::Exception::~Exception() throw()
{

}

TextureManager::Exception::Exception(const TextureManager::Exception &src) throw() :
  _what(src._what)
{

}

TextureManager::Exception	&TextureManager::Exception::operator=(const TextureManager::Exception &src) throw()
{
  if (&src != this)
    {
      this->_what = src._what;
    }
  return (*this);
}

const char		*TextureManager::Exception::what() const throw()
{
  return (this->_what.c_str());
}
