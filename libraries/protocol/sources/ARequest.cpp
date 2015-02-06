#include	"Protocol.hpp"
#include	"ARequest.hh"

ARequest::ARequest(const rtype::protocol::CodeID code):
  _code(code)
{

}

ARequest::~ARequest()
{

}

ARequest::ARequest(const ARequest &src):
  _code(src._code)
{

}

ARequest	&ARequest::operator=(const ARequest &src)
{
  if (&src != this)
    {
      _code = src._code;
    }
  return (*this);
}

rtype::protocol::CodeID	ARequest::code() const
{
  return (_code);
}

void			ARequest::code(const rtype::protocol::CodeID code)
{
  _code = code;
}

ARequest::Exception::Exception(const std::string &what) throw():
  _what(what)
{

}

ARequest::Exception::~Exception() throw()
{

}

ARequest::Exception::Exception(Exception const &src) throw() :
  _what(src._what)
{

}

ARequest::Exception	&ARequest::Exception::operator=(Exception const & src) throw()
{
  if (this != &src)
    {
      _what = src._what;
    }
  return (*this);
}

const char		*ARequest::Exception::what() const throw()
{
  return (_what.c_str());
}
