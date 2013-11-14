#pragma once

#include	"AGameRequest.hh"
#include	"protocol.hpp"

class LooseRequest : public AGameRequest
{
public:
	LooseRequest();
	~LooseRequest();

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone();
private:
};