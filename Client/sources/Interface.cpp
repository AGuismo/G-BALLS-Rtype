#include	"Interface.hh"

Interface::Interface()
{

}

Interface::~Interface()
{

}

Interface	&Interface::getInstance()
{
  static Interface	singleton;

  return (singleton);
}

void			Interface::addWidget(const std::string &key, AWidget *value)
{
  _lnk[key] = value;
}

void			Interface::delWidget(const std::string &key)
{
  _lnk.erase(key);
}

AWidget			*Interface::getWidget(const std::string &key)
{
  interface_type::iterator	it = _lnk.find(key);

  if (it == _lnk.end())
    return 0;
  return (it->second);
}
