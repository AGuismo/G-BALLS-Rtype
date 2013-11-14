#include "AliveRequest.h"

AliveRequest::AliveRequest(): AGameRequest(requestCode::game::ALIVE)
{}
AliveRequest::~AliveRequest()
{}

Protocol			&AliveRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID;
	return rhs;
}

Protocol			&AliveRequest::unserialize(Protocol &rhs)
{
	rhs >> _code >> _sessionID;
	return rhs;
}

ARequest			*AliveRequest::clone()
{
	return new AliveRequest();
}