#include "LeaveRequest.h"

LeaveRequest::LeaveRequest() : AGameRequest(requestCode::game::LEAVE)
{}

LeaveRequest::LeaveRequest(requestCode::SessionID id) : AGameRequest(requestCode::game::LEAVE, id)
{}

LeaveRequest::~LeaveRequest()
{}

Protocol			&LeaveRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID;
	return rhs;
}

Protocol			&LeaveRequest::unserialize(Protocol &rhs)
{
	rhs >> _sessionID;
	return rhs;
}

ARequest			*LeaveRequest::clone() const
{
	return new LeaveRequest();
}
