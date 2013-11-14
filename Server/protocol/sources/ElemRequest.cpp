#include "ElemRequest.hh"


ElemRequest::ElemRequest() : AGameRequest(requestCode::game::ELEM)
{
}

ElemRequest::ElemRequest(Rint8 type, Rint32 pos, Rint8 dir, Ruint16 id) :
	AGameRequest(requestCode::game::ELEM), _type(type), _pos(pos), _dir(dir), _id(id)
{}



ElemRequest::~ElemRequest()
{
}

Protocol			&ElemRequest::serialize(Protocol &rhs) const
{
	rhs << _code;
	rhs << _id;
	rhs << _type;
	rhs << _pos;
	rhs << _dir;
	return rhs;
}

Protocol			&ElemRequest::unserialize(Protocol &rhs)
{
	rhs >> _id;
	rhs >> _type;
	rhs >> _pos;
	rhs >> _dir;
	return rhs;
}

ARequest			*ElemRequest::clone()
{
	return (new ElemRequest(_type, _pos, _dir, _id));
}

Rint8			ElemRequest::type() const
{
	return _type;
}
void			ElemRequest::type(Rint8 t)
{
	_type = t;
}
Rint32			ElemRequest::pos() const
{
	return _pos;
}
void			ElemRequest::pos(Rint32 p)
{
	_pos = p;
}
Rint8			ElemRequest::dir() const
{
	return _dir;
}
void			ElemRequest::dir(Rint8 d)
{
	_dir = d;
}

Ruint16			ElemRequest::ID() const
{
	return _id;
}

void			ElemRequest::ID(Ruint16 id)
{
	_id = id;
}