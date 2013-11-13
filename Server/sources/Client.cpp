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

void			Client::update()
{
  if (_menu.inUse())
    _menu.update();
  else if (_game.inUse())
    _game.update();
}

void			Client::finalize()
{
  if (_menu.inUse())
    _menu.finalize();
  else if (_game.inUse())
    _game.finalize();
}

menu::Client		&Client::menu()
{
  return (_menu);
}

game::Client		&Client::game()
{
  return (_game);
}

ARequest		*Client::requestPop()
{
  if (_menu.inUse())
    return (_menu.requestPop());
  else if (_game.inUse())
    return (_game.requestPop());
  return (0); // it never happens...
}

void			Client::requestPush(ARequest *req)
{
  if (_menu.inUse())
    _menu.requestPush(req);
  else if (_game.inUse())
    _game.requestPush(req);
}
