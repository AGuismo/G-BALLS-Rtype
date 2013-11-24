#ifndef MENU_MANAGER_H_
# define MENU_MANAGER_H_

# include	<map>
# include	<list>
# include	"TcpServer.h"
# include	"streamManager.h"
# include	"Env.hh"
# include	"RequestCode.hh"
# include	"Bind.hpp"
# include	"ThreadEvent.hpp"
# include	"Threads.hpp"

class	Application;
class	ARequest;
class	Manager;
class	Game;
class	ICallbacks;

namespace	menu
{
  class Game;
  class	Client;
}

namespace	menu
{
  class		Manager
  {
    typedef Thread::EventQueue<ICallbacks *>	output_event;
    typedef Thread::EventQueue<ICallbacks *>	input_event;
    typedef std::list<Game *>			game_list;
    typedef std::list<Client *>			client_list;
    typedef void (*request_callback)(ARequest *, Client *, Manager *);
    typedef std::map<requestCode::CodeID, request_callback>	request_callback_map;
  public:
    Manager(Application *parent, input_event &input, output_event &output);
    virtual ~Manager();

  public:
    void	initialize(unsigned short int port = rtype::Env::TCP_SERVER_PORT);
    void	run();
	void	endGame(menu::Game *game);

  private:
    void	checkNewClient();
    void	updateCallback();
    void	updateClients();
    void	clientRequest(Client *client);

    template <typename Req>
    void	broadcast(const Req &req);

  private:
    struct	PredicateParty : std::unary_function<menu::Game *, bool>
    {
      PredicateParty(const std::string &partyName);
      bool	operator()(const menu::Game *);

      const std::string	_partyName;
    };

    struct	PredicateOwner : std::unary_function<menu::Game *, bool>
    {
      PredicateOwner(const Client *);
      bool	operator()(const menu::Game *);

      const Client	*_client;
    };

    struct	PredicateClient : std::unary_function< Client *, bool>
    {
      PredicateClient(const std::string &login);
      bool	operator()(const Client *client);

      const std::string	_login;
    };

    bool	isConnected(const std::string &login);

  private:
    static void	routine(Manager *);

  private:
    static void	tryConnect(ARequest *, Client *, Manager *);
    static void	newUser(ARequest *, Client *, Manager *);

    static void	launchGame(ARequest *, Client *, Manager *);
    static void	listGames(ARequest *, Client *, Manager *);
    static void	createGame(ARequest *, Client *, Manager *);
    static void	joinGame(ARequest *, Client *, Manager *);
    static void	cancelGame(ARequest *, Client *, Manager *);
    static void	shutdown(ARequest *, Client *, Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    Application				*_parent;
    Threads<void (*)(Manager *)>	_th;
    bool				_active;
    net::TcpServer			_server;
    net::streamManager			_monitor;
    client_list				_clients;
    input_event				&_input;
    output_event			&_output;
    request_callback_map		_requestCallback;
    game_list				_games;
  };

}

#endif /* MENU_MANAGER_H_ */
