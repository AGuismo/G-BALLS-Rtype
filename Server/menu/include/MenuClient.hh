#ifndef MENUCLIENT_H_
# define MENUCLIENT_H_

# include	<queue>
# include	<string>
# include	"RequestCode.hh"

class ARequest;
class RequestQueue;

namespace net
{
  class ClientAccepted;
}

namespace	menu
{
  class Client
  {
  public:
    Client(RequestQueue &input, RequestQueue &output,
	   net::ClientAccepted *clientTcp = 0);
    virtual ~Client();

  private:
    void		recvSock();
    void		sendSock();

  private:
    bool		inputRequest();
    bool		outputRequest();

  public:
    void		TcpLayer(net::ClientAccepted *);
    net::ClientAccepted	*TcpLayer() const;
    bool		isTCPDisconnected() const;
    bool		isTCP() const;
    void		closeTCP();

  public:
    void		update();

  private:
    Client(Client const&);
    Client& operator=(Client const&);

  public:
    void				username(const std::string &);
    const std::string			&username(void) const;
    void				password(const requestCode::PasswordType &);
    const requestCode::PasswordType	&password(void) const;
    void				sessionID(const requestCode::SessionID &);
    const requestCode::SessionID	&sessionID(void) const;
    void				authenticated(bool);
    bool				authenticated(void) const;

  public:
    bool	inUse(void) const {return (_used);};
    void	inUse(bool used) {_used = used;};

  private:
    bool		_used;
    RequestQueue	&_input;
    RequestQueue	&_output;
    net::ClientAccepted	*_TcpLayer;

  private:
    struct
    {
      bool				_authenticated;
      std::string			_username;
      requestCode::PasswordType		_password;
      requestCode::SessionID		_sessionID;
    }					_auth;
  };
}

#endif /* MENUCLIENT_H_ */
