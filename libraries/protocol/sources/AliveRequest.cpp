#include "AliveRequest.hh"

AliveRequest::AliveRequest(): AGameRequest(rtype::protocol::requestCode::game::ALIVE)
{}

AliveRequest::AliveRequest(rtype::protocol::SessionID id, rtype::protocol::game::Stamp stamp) : AGameRequest(rtype::protocol::requestCode::game::ALIVE, id, stamp)
{

}

AliveRequest::~AliveRequest()
{}

Protocol			&AliveRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _stamp;
	return rhs;
}

Protocol			&AliveRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID >> _stamp;
	return rhs;
}

ARequest			*AliveRequest::clone() const
{
	return new AliveRequest();
}
