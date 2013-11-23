#ifndef		__SCREEN_HH__
# define	__SCREEN_HH__

# include	<exception>
# include	<string>
# include	"IScreen.hh"

namespace	network
{
  class		Manager;
}

class AScreen : public IScreen
{
public:
  static const int	SCR_MENU = 0;
  static const int	SCR_GAME = 1;
  static const int	SCR_EXIT = 2;
public:
  enum Status
    {
      CONTINUE,
      START,
      EXIT,
      QUIT,
      LOGIN,
      CREATE_GAME,
      JOIN_GAME,
      REFRESH_GAME,
      BACK_MENU,
      SUBMIT,
      BACK_LOBY,
      VALIDE,
      SELECT_SERVER,
      SETTINGS,
      SET_CHANGE,
      INGAME,
      BACK_SET,
      VERIF_PWD,
      GAME
    };
protected:
  Status		_status;
  sf::Event		_event;
  sf::RenderWindow	&_window;
  network::Manager	&_network;

public:
  AScreen(sf::RenderWindow &window, network::Manager &manager, AScreen::Status status);
  virtual ~AScreen();
  virtual int	run(void) = 0;
  virtual void		clearWindow(void) = 0;
  virtual bool	load() = 0;

public:
  class Exception
  {
  public:
    Exception(const std::string &msg) throw();
    virtual ~Exception() throw();

  public:
    Exception(Exception const&) throw();
    Exception& operator=(Exception const&) throw();

  public:
    virtual const char	*what() const throw();

  private:
    std::string		_what;
  };
};

#endif	/* !__SCREEN_HH__ */
