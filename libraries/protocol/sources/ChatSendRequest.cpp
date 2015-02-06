#include "ChatSendRequest.hh"
#include "Protocol.hpp"

ChatSendRequest::ChatSendRequest() : ARequest(rtype::protocol::requestCode::chat::SEND_MSG)
{

}

ChatSendRequest::ChatSendRequest(const std::string &msg) : ARequest(rtype::protocol::requestCode::chat::SEND_MSG)
{
  _msg = msg;
}

ChatSendRequest::~ChatSendRequest()
{
}

ChatSendRequest::ChatSendRequest(ChatSendRequest const& src) : ARequest(rtype::protocol::requestCode::chat::SEND_MSG)
{
  _msg = src._msg;
}

ChatSendRequest& ChatSendRequest::operator=(ChatSendRequest const& src)
{
  if (&src != this)
  {
    _code = src._code;
    _msg = src._msg;
  }
  return (*this);
}

std::string ChatSendRequest::msg() const
{
  return _msg;
}


Protocol	&ChatSendRequest::serialize(Protocol &rhs) const
{
  rtype::protocol::Ruint16	len = _msg.length();

  rhs << _code << len;
  rhs.push(_msg, len);
  return (rhs);
}

Protocol	&ChatSendRequest::unserialize(Protocol &rhs)
{
  rtype::protocol::Ruint16	len;

  rhs >> len;
  rhs.pop(_msg, len);
  return (rhs);
}

ARequest	*ChatSendRequest::clone() const
{
  return (new ChatSendRequest(_msg));
}
