#include	"SessionRequest.hh"
#include	"Protocol.hpp"

SessionRequest::SessionRequest() :
  ARequest(requestCode::auth::SESSION), _sessionID(0)
{

}

SessionRequest::SessionRequest(const requestCode::SessionID id) :
  ARequest(requestCode::auth::SESSION), _sessionID(id)
{

}

SessionRequest::~SessionRequest()
{

}

SessionRequest::SessionRequest(SessionRequest const &src):
  ARequest(src), _sessionID(src._sessionID)
{

}

SessionRequest	&SessionRequest::operator=(SessionRequest const &src)
{
  if (&src != this)
    {
      _code = src._code;
      _sessionID = src._sessionID;
    }
  return (*this);
}

requestCode::SessionID	SessionRequest::SessionID() const
{
  return (_sessionID);
}

void			SessionRequest::SessionID(requestCode::SessionID id)
{
  _sessionID = id;
}

Protocol		&SessionRequest::serialize(Protocol &rhs) const
{
  rhs << _code << _sessionID;
  return (rhs);
}

Protocol		&SessionRequest::unserialize(Protocol &rhs)
{
  rhs >> _sessionID;
  return (rhs);
}

ARequest		*SessionRequest::clone() const
{
  return (new SessionRequest());
}

requestCode::SessionID	SessionRequest::Unique()
{
  static requestCode::SessionID	id = 0;

  return (++id);
}
