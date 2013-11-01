#ifndef CLIENT_H_
# define CLIENT_H_

namespace net
{
  class ClientAccepted;
}

class Client
{
public:
  Client();
  Client(net::ClientAccepted *);
  ~Client();

public:
  void			TcpLayer(net::ClientAccepted *);
  net::ClientAccepted	*TcpLayer() const;
  bool			isTCPDisconnected() const;
  bool			isTCP() const;
  void			closeTCP();

public:
  void			update();

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  net::ClientAccepted	*_TcpLayer;
};

#endif /* CLIENT_H_ */
