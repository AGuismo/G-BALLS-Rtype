#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class LooseRequest : public AGameRequest
{
public:
	LooseRequest();
	~LooseRequest();

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
	ARequest			*clone() const;
private:
};
