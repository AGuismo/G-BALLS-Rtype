#include	"MenuException.hh"

namespace	menu
{
  Exception::Exception(const std::string &msg) throw():
    _what(msg)
  {

  }

  Exception::Exception(const Exception &src) throw() :
    _what(src._what)
  {

  }

  Exception::~Exception() throw()
  {

  }

  Exception	&Exception::operator=(const Exception &src) throw()
  {
    if (&src != this)
      {
	_what = src._what;
      }
    return (*this);
  }

  const char	*Exception::what() const throw()
  {
    return (_what.c_str());
  }
}
