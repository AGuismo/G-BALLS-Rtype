#include	"GameClient.hh"

namespace	game
{
  Client::Client():
    _used(false)
  {

  }
  
  Client::Client(struct sockaddr_in addr) :
	  _used(false), _addr(addr)
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

  requestCode::SessionID	Client::SessionID() const
  {
    return (_id);
  }

  void				Client::SessionID(const requestCode::SessionID id)
  {
    _id = id;
  }

  void				Client::game(Game *game)
  {
    _game = game;
  }

  Game				*Client::game(void) const
  {
    return (_game);
  }

  void				Client::player(Player *player)
  {
    _player = player;
  }

  Player			*Client::player(void) const
  {
    return (_player);
  }
}
