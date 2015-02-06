#include	"AGameRequest.hh"

AGameRequest::AGameRequest(const rtype::protocol::CodeID code, rtype::protocol::SessionID id, rtype::protocol::game::Stamp stamp):
ARequest(code), _sessionID(id), _stamp(stamp)
{

}

AGameRequest::AGameRequest(const rtype::protocol::CodeID code):
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

rtype::protocol::SessionID	AGameRequest::SessionID() const
{
  return (_sessionID);
}

void			AGameRequest::SessionID(const rtype::protocol::SessionID id)
{
  _sessionID = id;
}

rtype::protocol::game::Stamp		AGameRequest::Stamp() const
{
	return (_stamp);
}

void			AGameRequest::Stamp(const rtype::protocol::game::Stamp stamp)
{
	_stamp = stamp;
}
