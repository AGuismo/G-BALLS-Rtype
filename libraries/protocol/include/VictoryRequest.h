#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class VictoryRequest : public AGameRequest
{
public:
  VictoryRequest();
  ~VictoryRequest();

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();
private:
};
