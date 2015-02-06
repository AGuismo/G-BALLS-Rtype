#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"

class DeathRequest : public AGameRequest
{
public:
  DeathRequest();
  DeathRequest(rtype::protocol::game::ID id, rtype::protocol::game::Stamp stamp);
  ~DeathRequest();

  DeathRequest(DeathRequest const&);
  DeathRequest& operator=(DeathRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone() const;

public:
  rtype::protocol::game::ID				ID() const;
  void				ID(rtype::protocol::game::ID id);

private:
  rtype::protocol::game::ID				_id;
};

