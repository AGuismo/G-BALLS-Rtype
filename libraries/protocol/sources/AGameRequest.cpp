#include	"AGameRequest.hh"

AGameRequest::AGameRequest(const requestCode::CodeID code, requestCode::SessionID id, game::Stamp stamp):
ARequest(code), _sessionID(id), _stamp(stamp)
{

}

AGameRequest::AGameRequest(const requestCode::CodeID code):
ARequest(code), _sessionID(0), _stamp(0)
{

}

AGameRequest::~AGameRequest()
{

}

AGameRequest::AGameRequest(const AGameRequest &src):
ARequest(src), _sessionID(src._sessionID), _stamp(src._stamp)
{

}

AGameRequest	&AGameRequest::operator=(const AGameRequest &src)
{
  if (&src != this)
    {
      _code = src._code;
      _sessionID = src._sessionID;
	  _stamp = src._stamp;
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

game::Stamp		AGameRequest::Stamp() const
{
	return (_stamp);
}

void			AGameRequest::Stamp(const game::Stamp stamp)
{
	_stamp = stamp;
}
