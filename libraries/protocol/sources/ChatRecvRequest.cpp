#include "ChatRecvRequest.h"
#include "Protocol.hpp"

ChatRecvRequest::ChatRecvRequest() : ARequest(requestCode::chat::RECV_MSG)
{
}

ChatRecvRequest::ChatRecvRequest(const std::string &msg) : ARequest(requestCode::chat::RECV_MSG)
{
	_msg = msg;
}

ChatRecvRequest::~ChatRecvRequest()
{
}

ChatRecvRequest::ChatRecvRequest(ChatRecvRequest const& src) : ARequest(requestCode::chat::RECV_MSG)
{
	_msg = src._msg;
}

ChatRecvRequest& ChatRecvRequest::operator=(ChatRecvRequest const& src)
{
	if (&src != this)
	{
		_code = src._code;
		_msg = src._msg;
	}
	return (*this);
}

std::string ChatRecvRequest::msg() const
{
	return _msg;
}


Protocol	&ChatRecvRequest::serialize(Protocol &rhs) const
{
	Ruint16	len = _msg.length();

	rhs << _code << len;
	rhs.push(_msg, len);
	return (rhs);
}

Protocol	&ChatRecvRequest::unserialize(Protocol &rhs)
{
	Ruint16	len;

	rhs >> len;
	rhs.pop(_msg, len);
	return (rhs);
}

ARequest	*ChatRecvRequest::clone() const
{
	return (new ChatRecvRequest(_msg));
}