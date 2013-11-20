#ifndef CLIENT_H_
# define CLIENT_H_

# include	<queue>
# include	"MenuClient.hh"
# include	"GameClient.hh"
# include	"RequestQueue.hh"

namespace net
{
  class ClientAccepted;
}

class ARequest;

class Client
{
public:
  Client();
  Client(net::ClientAccepted *);
  ~Client();

public:
/*  ARequest		*requestPop();
  void			requestPush(ARequest *);*/

public:
  void			update();
  bool			isUse() const;


public:
  menu::Client				&menu();
  game::Client				&game();
  const menu::Client			&menu() const;
  const game::Client			&game() const;
  requestCode::SessionID		&id();
  void					id(requestCode::SessionID id);

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  requestCode::SessionID	_id;
  menu::Client		_menu;
  game::Client		_game;
};

#endif /* CLIENT_H_ */
