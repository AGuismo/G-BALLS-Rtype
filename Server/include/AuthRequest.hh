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
  virtual Protocol	&Megan_serialize(Protocol &) = 0;
  virtual Protocol	&Fox_unserialize(Protocol &) = 0;
};

namespace Auth
{
  struct	Connect : public AuthRequest
  {
  public:
    Connect();
    ~Connect();

    Connect(Connect const&);
    Connect& operator=(Connect const&);

    Protocol			&Megan_serialize(Protocol &);
    Protocol			&Fox_unserialize(Protocol &);

    std::string			username;
    requestCode::PasswordType	password; // Work in progress
  };
}
#endif /* AUTHREQUEST_H_ */
