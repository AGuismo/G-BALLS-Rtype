#ifndef APPLICATION_H_
# define APPLICATION_H_

# include	<exception>
# include	<string>
# include	"MenuManager.hh"
# include	"GameManager.hh"
# include	"LoaderManager.hh"
# include	"ThreadEvent.hpp"

class	Game;

class Application
{
public:
  typedef Thread::EventQueue<Game *>		input_event;
  typedef Thread::EventQueue<ARequest *>	output_event;
  typedef std::vector<Client *>			client_list;
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
  void	run();

private:
  Application(Application const&);
  Application& operator=(Application const&);

private:
  input_event		_input;
  output_event		_output;
  menu::Manager		_menuManager;
  game::Manager		_gameManager;
  botLoader::Manager	_botLoaderManager;
  client_list		_clients;
};

#endif /* APPLICATION_H_ */
