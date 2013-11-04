#include	"Protocol.hpp"
#include	"AuthRequest.hh"

AuthRequest::AuthRequest(const requestCode::CodeID code) :
  ARequest(code)
{
}

AuthRequest::~AuthRequest()
{

}

AuthRequest::AuthRequest(AuthRequest const &src):
  ARequest(src)
{

}

AuthRequest	&AuthRequest::operator=(AuthRequest const &src)
{
  if (&src != this)
    {
      _code = src._code;
    }
  return (*this);
}

namespace Auth
{
  Connect::Connect():
    AuthRequest(requestCode::auth::CONNECT)
  {

  }

  Connect::~Connect()
  {

  }

  Connect::Connect(Connect const &src) :
    AuthRequest(src)
  {

  }

  Connect	&Connect::operator=(const Connect &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Connect::Megan_serialize(Protocol &rhs) const
  {
    requestCode::UsernameLen	len = username.size();

    rhs << len << username << password;
    return (rhs);
  }

  Protocol	&Connect::Fox_unserialize(Protocol &rhs)
  {
    requestCode::UsernameLen	len;

    rhs >> len;
    rhs >> username;
    rhs >> password;
    return (rhs);
  }

  ARequest	*Connect::clone()
  {
    return (new Connect());
  }
}
