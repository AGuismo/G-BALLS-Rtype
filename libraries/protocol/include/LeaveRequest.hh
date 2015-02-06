#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class LeaveRequest : public AGameRequest
{
public:
  LeaveRequest();
  LeaveRequest(rtype::protocol::SessionID, rtype::protocol::game::Stamp stamp);
	~LeaveRequest();

public:
	Protocol			&serialize(Protocol &) const;
	Protocol			&unserialize(Protocol &);
	ARequest			*clone() const;
private:
};

