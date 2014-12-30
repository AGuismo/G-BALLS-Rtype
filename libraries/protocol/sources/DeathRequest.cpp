#include "DeathRequest.h"
#include <iostream>

DeathRequest::DeathRequest() : AGameRequest(requestCode::game::DEATH)
{
}

DeathRequest::DeathRequest(Ruint16 id) :
AGameRequest(requestCode::game::DEATH), _id(id)
{
#if defined(DEBUG)
  std::cout << "Death Request on " << id << std::endl;
#endif
}

DeathRequest::~DeathRequest()
{
}

Protocol			&DeathRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _id;
	return rhs;
}

Protocol		&DeathRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID >> _id;
	return rhs;
}

ARequest		*DeathRequest::clone()
{
	return new DeathRequest(_id);
}

Ruint16			DeathRequest::ID() const
{
	return _id;
}

void			DeathRequest::ID(Ruint16 id)
{
	_id = id;
}
