#include	"FontManager.hh"
#include	"Font.hh"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{

}

FontManager	&FontManager::getInstance()
{
  static FontManager	*singleton = 0;

  if (singleton == 0)
    singleton = new FontManager;
  return (*singleton);
}

void			FontManager::addFont(const std::string &key, Font *value)
{
  _lnk[key] = value;
}

void			FontManager::addFont(const std::string &key, const std::string &path)
{
  sf::Font	font;
  Font		*tmp;

  if (!font.loadFromFile(path))
    throw Exception("Failed to load font location: " + path);
  tmp = new Font(font);
  addFont(key, tmp);
}

void			FontManager::delFont(const std::string &key)
{
  _lnk.erase(key);
}

Font			*FontManager::getFont(const std::string &key)
{
  Font_type::iterator	it = _lnk.find(key);

  if (it == _lnk.end())
    return 0;
  return (it->second);
}

FontManager::Exception::Exception(const std::string &msg) throw():
  _what(msg)
{

}

FontManager::Exception::~Exception() throw()
{

}

FontManager::Exception::Exception(const FontManager::Exception &src) throw() :
  _what(src._what)
{

}

FontManager::Exception	&FontManager::Exception::operator=(const FontManager::Exception &src) throw()
{
  if (&src != this)
    {
      this->_what = src._what;
    }
  return (*this);
}

const char		*FontManager::Exception::what() const throw()
{
  return (this->_what.c_str());
}
