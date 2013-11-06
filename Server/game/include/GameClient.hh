#ifndef GAMECLIENT_H_
# define GAMECLIENT_H_

# include	<queue>

class ARequest;
class RequestQueue;

namespace	game
{
  class Client
  {
  public:
    Client(RequestQueue &input, RequestQueue &output);
    virtual ~Client();

  public:
    void	update();

  private:
    Client(Client const&);
    Client& operator=(Client const&);

  public:
    bool	inUse(void) const {return (_used);};
    void	inUse(bool used) {_used = used;};

  private:
    bool		_used;
    RequestQueue	&_input;
    RequestQueue	&_output;
  };
}

#endif /* GAMECLIENT_H_ */
