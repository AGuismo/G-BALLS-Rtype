#include "VictoryRequest.hh"

VictoryRequest::VictoryRequest(): AGameRequest(rtype::protocol::requestCode::game::VICTORY)
{}
VictoryRequest::~VictoryRequest()
{}

Protocol			&VictoryRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _stamp;
	return rhs;
}

Protocol			&VictoryRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID >> _stamp;
	return rhs;
}

ARequest			*VictoryRequest::clone() const
{
	return new VictoryRequest();
}
