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
  virtual Protocol	&Megan_serialize(Protocol &) const = 0;
  virtual Protocol	&Fox_unserialize(Protocol &) = 0;
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
    Protocol			&Megan_serialize(Protocol &) const;
    Protocol			&Fox_unserialize(Protocol &);
    ARequest			*clone();

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
    Protocol			&Megan_serialize(Protocol &) const;
    Protocol			&Fox_unserialize(Protocol &);
    ARequest			*clone();

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
