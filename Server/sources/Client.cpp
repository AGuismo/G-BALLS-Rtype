#include	<iostream>
#include	"ClientAccepted.h"
#include	"ARequest.hh"
#include	"Client.hh"

Client::Client(net::ClientAccepted *clientTcp):
  _menu(_input, _output, clientTcp), _game(_input, _output)
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
  return (_output.requestPop());
}

void			Client::requestPush(ARequest *req)
{
  _input.requestPush(req);
}
