#include	"Protocol.hpp"
#include	"ARequest.hh"

ARequest::ARequest(const requestCode::CodeID code):
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

requestCode::CodeID	ARequest::code() const
{
  return (_code);
}

void			ARequest::code(const requestCode::CodeID code)
{
  _code = code;
}

Protocol	&ARequest::Megan_serialize(Protocol &transformer)
{
  transformer << _code;
  return (transformer);
}

Protocol	&ARequest::Fox_unserialize(Protocol &transformer)
{
  transformer >> _code;
  return (transformer);
}
