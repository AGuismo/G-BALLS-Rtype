#include	<string>
#include	<iostream>
#include	"Protocol.hpp"
#include	"AuthRequest.hh"
#include	"Env.hh"

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
  //////////////
  // NewUser  //
  //////////////

  NewUser::NewUser():
    AuthRequest(requestCode::auth::NEW_USER)
  {

  }

  NewUser::NewUser(const std::string &name, const requestCode::PasswordType pass):
    AuthRequest(requestCode::auth::NEW_USER), _username(name), _password(pass)
  {

  }

  NewUser::~NewUser()
  {

  }

  NewUser::NewUser(NewUser const &src) :
    AuthRequest(src), _username(src._username), _password(src._password)
  {

  }

  NewUser	&NewUser::operator=(const NewUser &src)
  {
    if (&src != this)
      {
	_code = src._code;
	_username = src._username;
	_password = src._password;
      }
    return (*this);
  }

  const std::string		&NewUser::username() const
  {
    return (_username);
  }

  const requestCode::PasswordType	&NewUser::password() const
  {
    return (_password);
  }

  Protocol			&NewUser::serialize(Protocol &rhs) const
  {
    requestCode::UsernameLen	len = _username.length();

    rhs << _code << len << _username;
    rhs.push(_password, rtype::Env::PASS_SIZE);
    return (rhs);
  }

  Protocol	&NewUser::unserialize(Protocol &rhs)
  {
    requestCode::UsernameLen	len;

    rhs >> len;
    rhs.pop(_username, len);
    rhs.pop(_password, rtype::Env::PASS_SIZE);
    return (rhs);
  }

  ARequest	*NewUser::clone()
  {
    return (new NewUser());
  }

  //////////////
  // Connect  //
  //////////////

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

  Protocol			&Connect::serialize(Protocol &rhs) const
  {
    requestCode::UsernameLen	len = _username.length();

    rhs << _code << len << _username;
    rhs.push(_password, rtype::Env::PASS_SIZE);
    return (rhs);
  }

  Protocol	&Connect::unserialize(Protocol &rhs)
  {
    requestCode::UsernameLen	len;

    rhs >> len;
    rhs.pop(_username, len);
    rhs.pop(_password, rtype::Env::PASS_SIZE);
    return (rhs);
  }

  ARequest	*Connect::clone()
  {
    return (new Connect());
  }

  /////////////////
  // ChangePass  //
  /////////////////

  ChangePass::ChangePass():
    AuthRequest(requestCode::auth::CHANGE_PASSWD)
  {

  }

  ChangePass::ChangePass(const std::string &name, const requestCode::PasswordType &curPass,
			 const requestCode::PasswordType &newPass, const requestCode::SessionID id):
    AuthRequest(requestCode::auth::CHANGE_PASSWD), _username(name), _curpassword(curPass),
    _newpassword(newPass), _sessionID(id)
  {

  }

  ChangePass::~ChangePass()
  {

  }

  ChangePass::ChangePass(ChangePass const &src) :
    AuthRequest(src), _username(src._username), _curpassword(src._curpassword),
    _newpassword(src._newpassword), _sessionID(src._sessionID)
  {

  }

  ChangePass	&ChangePass::operator=(const ChangePass &src)
  {
    if (&src != this)
      {
	_code = src._code;
	_username = src._username;
	_curpassword = src._curpassword;
	_newpassword = src._newpassword;
	_sessionID = src._sessionID;
      }
    return (*this);
  }

  const std::string		&ChangePass::username() const
  {
    return (_username);
  }

  const requestCode::PasswordType	&ChangePass::curpassword() const
  {
    return (_curpassword);
  }

  const requestCode::PasswordType	&ChangePass::newpassword() const
  {
    return (_newpassword);
  }

  requestCode::SessionID		ChangePass::sessionID() const
  {
    return (_sessionID);
  }

  Protocol			&ChangePass::serialize(Protocol &rhs) const
  {
    requestCode::UsernameLen	len = _username.length();

    rhs << _code << len << _username << _sessionID << _curpassword << _newpassword;
    return (rhs);
  }

  Protocol	&ChangePass::unserialize(Protocol &rhs)
  {
    requestCode::UsernameLen	len;

    rhs >> len;
    rhs.pop(_username, len);
    rhs >> _sessionID >> _curpassword >> _newpassword;
    return (rhs);
  }

  ARequest	*ChangePass::clone()
  {
    return (new ChangePass());
  }

}
