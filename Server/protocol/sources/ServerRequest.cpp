#include	<map>
#include	"ServerRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"

const char *ServerRequest::msg::OK = "OK";
const char *ServerRequest::msg::BAD_REQ = "Bad request";
const char *ServerRequest::msg::FORBIDDEN = "Forbidden request";
const char *ServerRequest::msg::NOT_IMPLEMENTED = "Request not implemented";
const char *ServerRequest::msg::NO_CONTENT = "No content found";
const char *ServerRequest::msg::PARTIAL_CONTENT = "Partial content";
const char *ServerRequest::msg::NO_SLOTS = "No slot available";

ServerRequest::ServerRequest(const requestCode::CodeID id):
  ARequest(id)
{
  if (id != requestCode::server::OK && id != requestCode::server::BAD_REQ &&
      id != requestCode::server::FORBIDDEN && id != requestCode::server::NOT_IMPLEMENTED &&
      id != requestCode::server::NO_CONTENT && id != requestCode::server::PARTIAL_CONTENT &&
      id != requestCode::server::NO_SLOTS)
    throw ARequest::Exception("Invalid Server Request");
}

ServerRequest::ServerRequest():
  ARequest(requestCode::server::OK)
{

}

ServerRequest::~ServerRequest()
{

}

ServerRequest::ServerRequest(ServerRequest const&src):
  ARequest(src)
{

}

ServerRequest&	ServerRequest::operator=(ServerRequest const&src)
{
  if (&src != this)
    {
      _code = src._code;
    }
  return (*this);
}

const char	*ServerRequest::getMsg(const requestCode::CodeID id)
{
  static std::map<requestCode::CodeID, const char *>	messages;

  if (messages.size() == 0)
    {
      messages[requestCode::server::OK] = msg::OK;
      messages[requestCode::server::BAD_REQ] = msg::BAD_REQ;
      messages[requestCode::server::FORBIDDEN] = msg::FORBIDDEN;
      messages[requestCode::server::NOT_IMPLEMENTED] = msg::NOT_IMPLEMENTED;
      messages[requestCode::server::NO_CONTENT] = msg::NO_CONTENT;
      messages[requestCode::server::PARTIAL_CONTENT] = msg::PARTIAL_CONTENT;
      messages[requestCode::server::NO_SLOTS] = msg::NO_SLOTS;
    }
  return (messages[id]);
}

Protocol			&ServerRequest::Megan_serialize(Protocol &rhs) const
{
  rhs << _code;
  return (rhs);
}

Protocol	&ServerRequest::Fox_unserialize(Protocol &rhs)
{
  return (rhs);
}

ARequest	*ServerRequest::clone()
{
  return (new ServerRequest());
}
