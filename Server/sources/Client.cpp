#include	<iostream>
#include	"ClientAccepted.h"
#include	"ARequest.hh"
#include	"Client.hh"

Client::Client(net::ClientAccepted *clientTcp):
  _menu(_id, clientTcp), _game(_id)
{
  _menu.inUse(true);
  _game.inUse(false);
}

Client::~Client()
{
}

void	Client::update()
{

}

bool	Client::isUse() const
{
  return (_menu.inUse() || _game.inUse());
}

const menu::Client		&Client::menu() const
{
  return (_menu);
}

const game::Client		&Client::game() const
{
  return (_game);
}

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
