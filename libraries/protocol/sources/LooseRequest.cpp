#include "LooseRequest.h"

LooseRequest::LooseRequest(): AGameRequest(requestCode::game::LOOSE)
{}
LooseRequest::~LooseRequest()
{}

Protocol			&LooseRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID;
	return rhs;
}

Protocol			&LooseRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID;
	return rhs;
}

ARequest			*LooseRequest::clone()
{
	return new LooseRequest();
}