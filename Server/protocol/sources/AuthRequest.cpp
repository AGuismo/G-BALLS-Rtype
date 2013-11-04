#include	<string>
#include	<iostream>
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

  Connect::Connect(const std::string &name, const requestCode::PasswordType pass):
    AuthRequest(requestCode::auth::CONNECT), _username(name), _password(pass)
  {

  }

  Connect::~Connect()
  {

  }

  Connect::Connect(Connect const &src) :
    AuthRequest(src), _username(src._username), _password(src._password)
  {

  }

  Connect	&Connect::operator=(const Connect &src)
  {
    if (&src != this)
      {
	_code = src._code;
	_username = src._username;
	_password = src._password;
      }
    return (*this);
  }

  const std::string		&Connect::username() const
  {
    return (_username);
  }

  const requestCode::PasswordType	&Connect::password() const
  {
    return (_password);
  }

  Protocol			&Connect::Megan_serialize(Protocol &rhs) const
  {
    requestCode::UsernameLen	len = _username.length();

    rhs << _code << len << _username << _password;
    return (rhs);
  }

  Protocol	&Connect::Fox_unserialize(Protocol &rhs)
  {
    requestCode::UsernameLen	len;

    rhs >> len;
    rhs.pop(_username, len);
    rhs >> _password;
    return (rhs);
  }

  ARequest	*Connect::clone()
  {
    return (new Connect());
  }
}
