#ifndef AUTHREQUEST_H_
# define AUTHREQUEST_H_

# include	<string>
# include	"RequestCode.hh"
# include	"ARequest.hh"

class AuthRequest : public ARequest
{
public:
  AuthRequest(const rtype::protocol::CodeID);
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
    Connect(const std::string &name, const rtype::protocol::PasswordType);
    ~Connect();

    Connect(Connect const&);
    Connect& operator=(Connect const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;

  public:
    const std::string			&username() const;
    const rtype::protocol::PasswordType	&password() const;

  private:
    std::string			_username;
    rtype::protocol::PasswordType	_password;
  };

  struct	NewUser : public AuthRequest
  {
  public:
    NewUser();
    NewUser(const std::string &name, const rtype::protocol::PasswordType);
    ~NewUser();

    NewUser(NewUser const&);
    NewUser& operator=(NewUser const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;

  public:
    const std::string			&username() const;
    const rtype::protocol::PasswordType	&password() const;

  private:
    std::string			_username;
    rtype::protocol::PasswordType	_password; // Work in progress
  };

  struct	ChangePass : public AuthRequest
  {
  public:
    ChangePass(const std::string &name, const rtype::protocol::PasswordType &curPass,
	       const rtype::protocol::PasswordType &newPass, const rtype::protocol::SessionID id);
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
    const rtype::protocol::PasswordType	&curpassword() const;
    const rtype::protocol::PasswordType	&newpassword() const;
    rtype::protocol::SessionID		sessionID() const;

  private:
    std::string			_username;
    rtype::protocol::PasswordType	_curpassword; // Work in progress
    rtype::protocol::PasswordType	_newpassword; // Work in progress
    rtype::protocol::SessionID	_sessionID;
  };
}
#endif /* AUTHREQUEST_H_ */
