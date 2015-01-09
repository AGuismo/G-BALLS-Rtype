#include "AliveRequest.h"

AliveRequest::AliveRequest(): AGameRequest(requestCode::game::ALIVE)
{}

AliveRequest::AliveRequest(requestCode::SessionID id) : AGameRequest(requestCode::game::ALIVE, id)
{

}

AliveRequest::~AliveRequest()
{}

Protocol			&AliveRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID;
	return rhs;
}

Protocol			&AliveRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID;
	return rhs;
}

ARequest			*AliveRequest::clone() const
{
	return new AliveRequest();
}