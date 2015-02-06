#ifndef MENUCLIENT_H_
# define MENUCLIENT_H_

# include	<string>
# include	<queue>
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
  class		Game;
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
    bool				inLobby(void) const;
    Game				*currentGame() const;
    void				currentGame(Game *);
    void				username(const std::string &);
    const std::string			&username(void) const;
    void				password(const rtype::protocol::PasswordType &);
    const rtype::protocol::PasswordType	&password(void) const;
    void				sessionID(const rtype::protocol::SessionID &);
    const rtype::protocol::SessionID	&sessionID(void) const;
    void				permissions(rtype::protocol::database::Rights);
    rtype::protocol::database::Rights			permissions(void) const;
    void				authenticated(bool);
    bool				authenticated(void) const;

  private:
    RequestQueue		_input;
    RequestQueue		_output;
    net::ClientAccepted		*_TcpLayer;
    rtype::protocol::SessionID	_id;
    Game			*_game;

  private:
    struct
    {
      bool				_authenticated;
      std::string			_username;
      rtype::protocol::PasswordType		_password;
      rtype::protocol::database::Rights			_permissions;
    }					_auth;
  };
}

#endif /* MENUCLIENT_H_ */
