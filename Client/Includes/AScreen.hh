//
// Screen.hh for screen in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 15:14:30 2013 brigno
// Last update Wed Nov  6 04:04:27 2013 brigno
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
      EXIT,
      QUIT,
      CHANGE_SCR
    };
protected:
  Status		_status;
  sf::Event		_event;
  sf::RenderWindow	_window;
  Network		*_network;

public:
  AScreen(const std::string &name, int width, int height, Network *network, AScreen::Status status);
  ~AScreen();
  virtual int	run(void) = 0;

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
