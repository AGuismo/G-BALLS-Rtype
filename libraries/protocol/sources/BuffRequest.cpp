#include "BuffRequest.h"

BuffRequest::BuffRequest() : AGameRequest(requestCode::game::BUFF)
{

}

BuffRequest::BuffRequest(Ruint16 id, Rint8 type) :
AGameRequest(requestCode::game::BUFF), _id(id), _type(type)
{

}

BuffRequest::~BuffRequest()
{}

Protocol			&BuffRequest::serialize(Protocol &rhs) const
{
	rhs << _id;
	rhs << _type;
	return rhs;
}

Protocol		&BuffRequest::unserialize(Protocol &rhs)
{
	rhs >> _id;
	rhs >> _type;
	return rhs;
}

ARequest		*BuffRequest::clone() const
{
	return new BuffRequest(_id, _type);
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