#include	"NetException.h"

using namespace net;

Exception::Exception(const std::string &error) throw()
{
  _what = std::string("Network Exception, error detail: " + error).c_str();
}

Exception::Exception(const Exception &src) throw() :
  _what(src._what)
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

Exception::~Exception() throw()
{

}

const char	*Exception::what() const throw()
{
  return (_what);
}
