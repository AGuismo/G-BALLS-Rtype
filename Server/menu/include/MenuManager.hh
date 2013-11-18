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

class Client;
class ARequest;
class Manager;
namespace	menu
{
  class Game;
}

namespace	menu
{
  class		Manager
  {
    typedef std::list<Game *>		game_list;
    typedef std::list< ::Client *>	client_list;
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
      PredicateOwner(const ::Client *);
      bool	operator()(const menu::Game *);

      const ::Client	*_client;
    };

    struct	PredicateClient : std::unary_function< ::Client *, bool>
    {
      PredicateClient(const std::string &login);
      bool	operator()(const ::Client *client);

      const std::string	_login;
    };

    bool	isConnected(const std::string &login);

  private:
    static void	routine(Manager *);

  private:
    static void	tryConnect(ARequest *, ::Client *, Manager *);
    static void	newUser(ARequest *, ::Client *, Manager *);

    static void	launchGame(ARequest *, ::Client *, Manager *);
    static void	listGames(ARequest *, ::Client *, Manager *);
    static void	createGame(ARequest *, ::Client *, Manager *);
    static void	joinGame(ARequest *, ::Client *, Manager *);
    static void	cancelGame(ARequest *, ::Client *, Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    net::TcpServer			_server;
    net::streamManager			_monitor;
    client_list				_clients;
    Thread::EventQueue<ARequest *>	&_input;
    Thread::EventQueue<ARequest *>	&_output;
    request_callback_map		_requestCallback;
    game_list				_games;
  };

}

#endif /* MENU_MANAGER_H_ */
