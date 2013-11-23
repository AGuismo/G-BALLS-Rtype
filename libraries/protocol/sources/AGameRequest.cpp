#include	"AGameRequest.hh"

AGameRequest::AGameRequest(const requestCode::CodeID code):
  ARequest(code), _sessionID(0)
{

}

AGameRequest::~AGameRequest()
{

}

AGameRequest::AGameRequest(const AGameRequest &src):
  ARequest(src), _sessionID(src._sessionID)
{

}

AGameRequest	&AGameRequest::operator=(const AGameRequest &src)
{
  if (&src != this)
    {
      _code = src._code;
      _sessionID = src._sessionID;
    }
  return (*this);
}

requestCode::SessionID	AGameRequest::SessionID() const
{
  return (_sessionID);
}

void			AGameRequest::SessionID(const requestCode::SessionID id)
{
  _sessionID = id;
}
