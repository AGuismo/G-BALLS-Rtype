#include "ElemRequest.hh"
#include <iostream>

ElemRequest::ElemRequest() : AGameRequest(requestCode::game::ELEM)
{
}

ElemRequest::ElemRequest(game::Type type, game::Pos pos, game::Dir dir, game::ID id) :
  AGameRequest(requestCode::game::ELEM), _type(type), _pos(pos), _dir(dir), _id(id)
{
#if defined(DEBUG)
	std::cout << "Creating ElemRequest with param : " << std::endl <<
		"type : " << (int)type << std::endl <<
		"pos : " << pos << std::endl <<
		"dir : " << (int)dir << std::endl <<
		"id : " << id << std::endl;
#endif
}



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

game::Type			ElemRequest::type() const
{
  return _type;
}
void			ElemRequest::type(game::Type t)
{
  _type = t;
}

game::Pos			ElemRequest::pos() const
{
  return _pos;
}

void			ElemRequest::pos(game::Pos p)
{
  _pos = p;
}

game::Dir			ElemRequest::dir() const
{
  return _dir;
}

void			ElemRequest::dir(game::Dir d)
{
  _dir = d;
}

game::ID			ElemRequest::ID() const
{
  return _id;
}

void			ElemRequest::ID(game::ID id)
{
  _id = id;
}
