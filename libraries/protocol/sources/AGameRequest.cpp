#include	"AGameRequest.hh"

AGameRequest::AGameRequest(const requestCode::CodeID code, requestCode::SessionID id):
  ARequest(code), _sessionID(id)
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
