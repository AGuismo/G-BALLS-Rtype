#ifndef MENU_MANAGER_H_
# define MENU_MANAGER_H_

# include	"TcpServer.h"
# include	"streamManager.h"
# include	"Env.hh"

class Client;

namespace	menu
{
  class		Manager
  {
  public:
    Manager();
    virtual ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::TCP_SERVER_PORT);
    void	run();

  private:
    void	checkNewClient();
    void	updateClients();

  private:
    static void	routine(Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    net::TcpServer		_server;
    net::streamManager		_monitor;
    std::vector<Client *>	_clients;
  };

}

#endif /* MENU_MANAGER_H_ */
