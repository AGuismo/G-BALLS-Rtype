#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class LeaveRequest : public AGameRequest
{
public: 
  LeaveRequest();
  LeaveRequest(requestCode::SessionID);
	~LeaveRequest();

public:
	Protocol			&serialize(Protocol &) const;
	Protocol			&unserialize(Protocol &);
	ARequest			*clone();
private:
};

