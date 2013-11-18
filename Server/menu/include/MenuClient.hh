#ifndef MENUCLIENT_H_
# define MENUCLIENT_H_

# include	<queue>
# include	<string>
# include	"RequestCode.hh"
# include	"RequestQueue.hh"

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
    Client(net::ClientAccepted *clientTcp = 0);
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
    void		finalize();

  public:
    ARequest		*requestPop();
    void		requestPush(ARequest *req);

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
    void				permissions(database::Rights);
    database::Rights			permissions(void) const;
    void				authenticated(bool);
    bool				authenticated(void) const;

  public:
    bool	inUse(void) const {return (_used);};
    void	inUse(bool used) {_used = used;};

  private:
    bool		_used;
    RequestQueue	_input;
    RequestQueue	_output;
    net::ClientAccepted	*_TcpLayer;

  private:
    struct
    {
      bool				_authenticated;
      std::string			_username;
      requestCode::PasswordType		_password;
      requestCode::SessionID		_sessionID;
      database::Rights			_permissions;
    }					_auth;
  };
}

#endif /* MENUCLIENT_H_ */
