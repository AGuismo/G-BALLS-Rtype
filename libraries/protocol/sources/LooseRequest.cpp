#include "LooseRequest.hh"

LooseRequest::LooseRequest(): AGameRequest(requestCode::game::LOOSE)
{}
LooseRequest::~LooseRequest()
{}

Protocol			&LooseRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _stamp;
	return rhs;
}

Protocol			&LooseRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID >> _stamp;
	return rhs;
}

ARequest			*LooseRequest::clone() const
{
	return new LooseRequest();
}
