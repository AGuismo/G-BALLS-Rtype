#include	"GameClient.hh"

namespace	game
{
  Client::Client():
    _used(false)
  {

  }

  Client::~Client()
  {

  }

  void	Client::update()
  {

  }

  void	Client::finalize()
  {

  }

  ARequest	*Client::requestPop()
  {
    return (_input.requestPop());
  }

  void		Client::requestPush(ARequest *req)
  {
    _output.requestPush(req);
  }
}
