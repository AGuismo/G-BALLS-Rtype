#include "EventRequest.hh"

EventRequest::EventRequest(Ruint8 event, Ruint8 param): AGameRequest(requestCode::game::EVENT), _event(event), _param(param)
{
}

EventRequest::~EventRequest()
{
}

EventRequest::EventRequest(EventRequest const&src): AGameRequest(requestCode::game::EVENT)
{
}
Ruint8				EventRequest::event()const
{
	return _event;
}
void				EventRequest::event(const Ruint8 &event)
{
	_event = event;
}
Ruint8				EventRequest::param()const
{
	return _param;
}
void				EventRequest::param(const Ruint8 &param)
{
	_param = param;
}

Protocol			&EventRequest::serialize(Protocol &rhs) const
{
	rhs << _code << _sessionID << _event << _param;
	return rhs;
}

Protocol			&EventRequest::unserialize(Protocol &rhs)
{
	rhs >> _code >> _sessionID >> _event >> _param;
	return rhs;
}

ARequest			*EventRequest::clone()
{
	return new EventRequest(*this);
}