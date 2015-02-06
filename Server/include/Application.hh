#ifndef APPLICATION_H_
# define APPLICATION_H_

# include	<exception>
# include	<string>
# include	<list>
# include	<set>
# include	<fstream>
// # include	"MenuManager.hh"
// # include	"GameManager.hh"
# include	"LoaderManager.hh"
# include	"ThreadEvent.hpp"
# include	"ProtocolTypes.hh"
# include	"Log.hh"

#if defined(WIN32)
#pragma warning( disable : 4251)
#pragma warning( disable : 4244)
#endif

class	Client;
class	ICallbacks;
class	IApplicationCallbacks;

namespace game
{
  class Manager;
  class Game;
  class Client;
}

namespace menu
{
  class Manager;
  class Game;
  class Client;
}

class Application
{
public:
  typedef Thread::EventQueue<ICallbacks *>		input_event;
  typedef Thread::EventQueue<IApplicationCallbacks *>	output_event;
  typedef std::list<Client *>				client_list;
  typedef std::pair<menu::Game *, game::Game *>		game_pair;
  typedef std::list<game_pair>				game_list;

public:
  class InitExcept : public std::exception
  {
  public:
    virtual const char	*what() const throw();
    InitExcept(const std::string &) throw();
    InitExcept(const InitExcept &) throw();
    virtual ~InitExcept() throw();

  public:
    InitExcept& operator=(InitExcept const&) throw();

  private:
    std::string		_what;
  };

public:
  Application();
  virtual ~Application();

public:
  static loglib::Log	log;

public:
  void	stop(menu::Client *);
  void	run();
  void	routine();

public:
  void	newClient(rtype::protocol::SessionID clientID);
  void  clientDisconnected(rtype::protocol::SessionID clientID);
  void	newGame(menu::Game *game);
  void	endGame(const game::Game *game);
  void	cancelGame(const game::Game *game);
  void	ClientLeaveGame(rtype::protocol::SessionID clientID);

private:
  Application(Application const&);
  Application& operator=(Application const&);

private:
  bool			_active;
  input_event		_gameOutput;
  input_event		_menuOutput;
  output_event		_input;
  std::ofstream		_log;
  menu::Manager		*_menuManager;
  game::Manager		*_gameManager;
  botLoader::Manager	_botLoaderManager;
  client_list		_clients;
  game_list		_games;

private:
  struct	PredicateClient : public std::unary_function<Client *, bool>
  {
    PredicateClient(rtype::protocol::SessionID client);
    bool	operator()(const Client *);

    rtype::protocol::SessionID	_client;
  };

  struct	PredicateGame : public std::unary_function<game_pair, bool>
  {
    PredicateGame(const game::Game *);
    bool	operator()(const game_pair &);

    const game::Game	*_game;
  };

};

#endif /* APPLICATION_H_ */
