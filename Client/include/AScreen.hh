//
// Screen.hh for screen in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 15:14:30 2013 brigno
// Last update Thu Nov 21 02:00:56 2013 lambert kevin
//

#ifndef		__SCREEN_HH__
# define	__SCREEN_HH__

# include	<exception>
# include	<string>
# include	"IScreen.hh"

class		Network;

class AScreen : public IScreen
{
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
      SELECT_SERVER
    };
protected:
  Status		_status;
  sf::Event		_event;
  sf::RenderWindow	&_window;
  Network		*_network;

public:
  AScreen(sf::RenderWindow &window, AScreen::Status status);
  ~AScreen();
  virtual void	run(void) = 0;
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
