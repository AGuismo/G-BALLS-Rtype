#include "BuffRequest.hh"

BuffRequest::BuffRequest() : AGameRequest(requestCode::game::BUFF)
{

}

BuffRequest::BuffRequest(Ruint16 id, Rint8 type, game::Stamp stamp) :
  AGameRequest(requestCode::game::BUFF, 0, stamp), _id(id), _type(type)
{

}

BuffRequest::~BuffRequest()
{}

BuffRequest::BuffRequest(BuffRequest const&src):
  AGameRequest(src)
{
  _id = src._id;
  _type = src._type;
}

BuffRequest& BuffRequest::operator=(BuffRequest const&src)
{
  if (&src != this)
  {
    AGameRequest::operator=(src);
    _id = src._id;
    _type = src._type;
  }
  return (*this);
}


Protocol			&BuffRequest::serialize(Protocol &rhs) const
{
  rhs << _code << _sessionID << _stamp;
  rhs << _id;
  rhs << _type;
  return rhs;
}

Protocol		&BuffRequest::unserialize(Protocol &rhs)
{
  rhs >> _sessionID >> _stamp;
  rhs >> _id;
  rhs >> _type;
  return rhs;
}

ARequest		*BuffRequest::clone() const
{
  return new BuffRequest(*this);
}

Ruint16			BuffRequest::ID() const
{
  return _id;
}

void			BuffRequest::ID(Ruint16 id)
{
  _id = id;
}

Rint8				BuffRequest::type() const
{
  return _type;
}

void				BuffRequest::type(Rint8 type)
{
  _type = type;
}
