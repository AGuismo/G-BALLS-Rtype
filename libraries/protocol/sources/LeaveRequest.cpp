#include "LeaveRequest.hh"

LeaveRequest::LeaveRequest() : AGameRequest(rtype::protocol::requestCode::game::LEAVE)
{}

LeaveRequest::LeaveRequest(rtype::protocol::SessionID id, rtype::protocol::game::Stamp stamp) : AGameRequest(rtype::protocol::requestCode::game::LEAVE, id, stamp)
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
