#include "DeathRequest.h"

DeathRequest::DeathRequest() : AGameRequest(requestCode::game::DEATH)
{
}

DeathRequest::DeathRequest(Ruint16 id) :
AGameRequest(requestCode::game::DEATH), _id(id)
{
}

DeathRequest::~DeathRequest()
{
}

Protocol			&DeathRequest::serialize(Protocol &rhs) const
{
	rhs << _id;
	return rhs;
}

Protocol		&DeathRequest::unserialize(Protocol &rhs)
{
	rhs >> _id;
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