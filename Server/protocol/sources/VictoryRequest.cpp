#include "VictoryRequest.h"

VictoryRequest::VictoryRequest(): AGameRequest(requestCode::game::VICTORY)
{}
VictoryRequest::~VictoryRequest()
{}

Protocol			&VictoryRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID;
	return rhs;
}

Protocol			&VictoryRequest::unserialize(Protocol &rhs)
{
	rhs >> _code >> _sessionID;
	return rhs;
}

ARequest			*VictoryRequest::clone()
{
	return new VictoryRequest();
}