#include "DeathRequest.hh"
#include <iostream>

DeathRequest::DeathRequest() : AGameRequest(rtype::protocol::requestCode::game::DEATH)
{
}

DeathRequest::DeathRequest(rtype::protocol::Ruint16 id, rtype::protocol::game::Stamp stamp) :
  AGameRequest(rtype::protocol::requestCode::game::DEATH, 0, stamp), _id(id)
{
#if defined(DEBUG)
  std::cout << "Death Request on " << id << std::endl;
#endif
}

DeathRequest::~DeathRequest()
{
}

DeathRequest::DeathRequest(DeathRequest const&src):
  AGameRequest(src), _id(src._id)
{
}

DeathRequest& DeathRequest::operator=(DeathRequest const&src)
{
  if (&src != this)
  {
    AGameRequest::operator=(src);
    _id = src._id;
  }
  return (*this);
}


Protocol			&DeathRequest::serialize(Protocol &rhs) const
{
  rhs << _code << _sessionID << _stamp << _id;
  return rhs;
}

Protocol		&DeathRequest::unserialize(Protocol &rhs)
{
  rhs >> _sessionID >> _stamp >> _id;
  return rhs;
}

ARequest		*DeathRequest::clone() const
{
  return new DeathRequest(*this);
}

rtype::protocol::game::ID			DeathRequest::ID() const
{
  return _id;
}

void			DeathRequest::ID(rtype::protocol::game::ID id)
{
  _id = id;
}
