#include	<map>
#include	"ServerRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"
#include	"RequestInfo.hpp"

const char *detail::OK = "OK";
const char *detail::BAD_REQ = "Bad request";
const char *detail::FORBIDDEN = "Forbidden request";
const char *detail::NOT_IMPLEMENTED = "Request not implemented";
const char *detail::NO_CONTENT = "No content found";
const char *detail::PARTIAL_CONTENT = "Partial content";
const char *detail::NO_SLOTS = "No slot available";

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

Protocol	&ServerRequest::serialize(Protocol &rhs) const
{
  rhs << _code;
  return (rhs);
}

Protocol	&ServerRequest::unserialize(Protocol &rhs)
{
  return (rhs);
}

ARequest	*ServerRequest::clone() const
{
  return (new ServerRequest());
}
