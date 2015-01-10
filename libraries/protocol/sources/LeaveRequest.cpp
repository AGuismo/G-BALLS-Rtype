#include "LeaveRequest.h"

LeaveRequest::LeaveRequest() : AGameRequest(requestCode::game::LEAVE)
{}

LeaveRequest::LeaveRequest(requestCode::SessionID id, game::Stamp stamp) : AGameRequest(requestCode::game::LEAVE, id, stamp)
{}

LeaveRequest::~LeaveRequest()
{}

Protocol			&LeaveRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _stamp;
	return rhs;
}

Protocol			&LeaveRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID << _stamp;
	return rhs;
}

ARequest			*LeaveRequest::clone() const
{
	return new LeaveRequest();
}
