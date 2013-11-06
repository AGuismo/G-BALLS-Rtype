#ifndef GAMECLIENT_H_
# define GAMECLIENT_H_

# include	<queue>
# include	"RequestQueue.hh"

class ARequest;

namespace	game
{
  class Client
  {
  public:
    Client();
    virtual ~Client();

  public:
    void	update();
    void	finalize();

  private:
    Client(Client const&);
    Client& operator=(Client const&);

  public:
    bool	inUse(void) const {return (_used);};
    void	inUse(bool used) {_used = used;};

  public:
    ARequest		*requestPop();
    void		requestPush(ARequest *req);

  private:
    bool		_used;
    RequestQueue	_input;
    RequestQueue	_output;
  };
}

#endif /* GAMECLIENT_H_ */
