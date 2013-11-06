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
  ARequest		*requestPop();
  void			requestPush(ARequest *);

public:
  void			update();
  void			finalize();

public:
  menu::Client		&menu();
  game::Client		&game();

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  RequestQueue		_input;
  RequestQueue		_output;
  menu::Client		_menu;
  game::Client		_game;
};

#endif /* CLIENT_H_ */
