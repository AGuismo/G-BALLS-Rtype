#include "LeaveRequest.h"

LeaveRequest::LeaveRequest() : AGameRequest(requestCode::game::LEAVE)
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

ARequest			*LeaveRequest::clone()
{
	return new LeaveRequest();
}