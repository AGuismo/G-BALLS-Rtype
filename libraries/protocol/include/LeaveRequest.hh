#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class LeaveRequest : public AGameRequest
{
public: 
  LeaveRequest();
  LeaveRequest(requestCode::SessionID, game::Stamp stamp);
	~LeaveRequest();

public:
	Protocol			&serialize(Protocol &) const;
	Protocol			&unserialize(Protocol &);
	ARequest			*clone() const;
private:
};

