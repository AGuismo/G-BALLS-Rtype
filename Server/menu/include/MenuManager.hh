#ifndef MENU_MANAGER_H_
# define MENU_MANAGER_H_

# include	<map>
# include	"TcpServer.h"
# include	"streamManager.h"
# include	"Env.hh"
# include	"RequestCode.hh"
# include	"Bind.hpp"
# include	"ThreadEvent.hpp"

class Client;
class ARequest;
class Manager;
class Game;

namespace	menu
{
  class		Manager
  {
    typedef void (*request_callback)(ARequest *, ::Client *, Manager *);
    typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;
  public:
	  Manager(Thread::EventQueue<ARequest *> &input, Thread::EventQueue<ARequest *> &output);
    virtual ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::TCP_SERVER_PORT);
    void	run();

  private:
    void	checkNewClient();
    void	updateClients();
    void	clientRequest(::Client *client);
    void	sendGame(Game *game);

  private:
    static void	routine(Manager *);

  private:
    static void	tryConnect(ARequest *, ::Client *, Manager *);
    static void	launchGame(ARequest *, ::Client *, Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    net::TcpServer		_server;
    net::streamManager		_monitor;
    std::vector< ::Client *>	_clients;
    Thread::EventQueue<ARequest *>		&_input;
    Thread::EventQueue<ARequest *>		&_output;
    request_callback_map	_requestCallback;
  };

}

#endif /* MENU_MANAGER_H_ */
