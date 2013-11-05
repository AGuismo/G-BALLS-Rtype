#ifndef CLIENT_H_
# define CLIENT_H_

# include	<queue>

namespace net
{
  class ClientAccepted;
}

class Client
{
  typedef std::queue<ARequest *>	request_queue;
public:
  Client();
  Client(net::ClientAccepted *);
  ~Client();

private:
  void			recvSock();
  bool			request();

public:
  void			TcpLayer(net::ClientAccepted *);
  net::ClientAccepted	*TcpLayer() const;
  bool			isTCPDisconnected() const;
  bool			isTCP() const;
  void			closeTCP();

public:
  void			update();

public:
  ARequest		*requestPop();
  // void			requestPush(ARequest *);

public:
  void					username(const std::string &);
  const std::string			&username(void) const;
  void					password(const requestCode::PasswordType &);
  const requestCode::PasswordType	&password(void) const;
  void					sessionID(const requestCode::SessionID &);
  const requestCode::SessionID		&sessionID(void) const;

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  net::ClientAccepted		*_TcpLayer;
  request_queue			_queue;

  std::string			_username;
  requestCode::PasswordType	_password;
  requestCode::SessionID	_sessionID;
};

#endif /* CLIENT_H_ */
