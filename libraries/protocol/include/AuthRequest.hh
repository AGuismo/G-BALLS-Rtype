#ifndef AUTHREQUEST_H_
# define AUTHREQUEST_H_

# include	<string>
# include	"RequestCode.hh"
# include	"ARequest.hh"

class AuthRequest : public ARequest
{
public:
  AuthRequest(const requestCode::CodeID);
  virtual ~AuthRequest();

public:
  AuthRequest(AuthRequest const&);
  AuthRequest& operator=(AuthRequest const&);

public:
  virtual Protocol	&serialize(Protocol &) const = 0;
  virtual Protocol	&unserialize(Protocol &) = 0;
};

namespace Auth
{
  struct	Connect : public AuthRequest
  {
  public:
    Connect();
    Connect(const std::string &name, const requestCode::PasswordType);
    ~Connect();

    Connect(Connect const&);
    Connect& operator=(Connect const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;

  public:
    const std::string			&username() const;
    const requestCode::PasswordType	&password() const;

  private:
    std::string			_username;
    requestCode::PasswordType	_password;
  };

  struct	NewUser : public AuthRequest
  {
  public:
    NewUser();
    NewUser(const std::string &name, const requestCode::PasswordType);
    ~NewUser();

    NewUser(NewUser const&);
    NewUser& operator=(NewUser const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;

  public:
    const std::string			&username() const;
    const requestCode::PasswordType	&password() const;

  private:
    std::string			_username;
    requestCode::PasswordType	_password; // Work in progress
  };

  struct	ChangePass : public AuthRequest
  {
  public:
    ChangePass(const std::string &name, const requestCode::PasswordType &curPass,
	       const requestCode::PasswordType &newPass, const requestCode::SessionID id);
    ChangePass();
    ~ChangePass();

    ChangePass(ChangePass const&);
    ChangePass& operator=(ChangePass const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;

  public:
    const std::string			&username() const;
    const requestCode::PasswordType	&curpassword() const;
    const requestCode::PasswordType	&newpassword() const;
    requestCode::SessionID		sessionID() const;

  private:
    std::string			_username;
    requestCode::PasswordType	_curpassword; // Work in progress
    requestCode::PasswordType	_newpassword; // Work in progress
    requestCode::SessionID	_sessionID;
  };
}
#endif /* AUTHREQUEST_H_ */
