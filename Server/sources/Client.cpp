#include	<iostream>
#include	"MenuClient.hh"
#include	"GameClient.hh"
#include	"ClientAccepted.h"
#include	"ARequest.hh"
#include	"Client.hh"

Client::Client():
  _id(0), _state(NONE)
{
}

Client::Client(requestCode::SessionID id, State st):
  _id(id), _state(st)
{
}

Client::~Client()
{
}

const requestCode::SessionID	&Client::id() const
{
  return _id;
}

void	Client::id(requestCode::SessionID id)
{
  _id = id;
}

Client::State			Client::state() const
{
  return (_state);
}

void				Client::state(State st)
{
  _state = st;
}

requestCode::SessionID		Client::generateUniqueID()
{
  static requestCode::SessionID	id = 1;

  return (id++);
}
