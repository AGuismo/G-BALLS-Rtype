#include	<iostream>
#include	"ClientAccepted.h"
#include	"ARequest.hh"
#include	"Client.hh"

Client::Client(net::ClientAccepted *clientTcp):
  _menu(clientTcp)
{
  _menu.inUse(true);
  _game.inUse(false);
}

Client::~Client()
{
}

void			Client::finalize()
{
  if (_menu.inUse())
    _menu.finalize();
  else if (_game.inUse())
    _game.finalize();
} 
/*lemart et gherab aimerai comprendre l'utilité de ce machin
juste au dessus,
car il n'ont pas réussi a le comprendre par eux meme*/

menu::Client		&Client::menu()
{
  return (_menu);
}

game::Client		&Client::game()
{
  return (_game);
}

requestCode::SessionID	&Client::id()
{
	return _id;
}

void	Client::id(requestCode::SessionID id)
{
	_id = id;
}



/*ARequest		*Client::requestPop()
{
  if (_menu.inUse())
    return (_menu.requestPop());
  else if (_game.inUse())
    return (_game.requestPop());
  return (0); // it never happens...
}*/

/*void			Client::requestPush(ARequest *req)
{
  if (_menu.inUse())
    _menu.requestPush(req);
  else if (_game.inUse())
    _game.requestPush(req);
}*/
