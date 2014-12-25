#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class AliveRequest : public AGameRequest
{
public:
	AliveRequest();
	AliveRequest(requestCode::SessionID id);
	~AliveRequest();

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();
private:
};
