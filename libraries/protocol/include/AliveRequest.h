#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class AliveRequest : public AGameRequest
{
public:
	AliveRequest();
	AliveRequest(requestCode::SessionID id, game::Stamp stamp);
	~AliveRequest();

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone() const;
private:
};
