#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"

class DeathRequest : public AGameRequest
{
public:
	DeathRequest();
	DeathRequest(Ruint16 id);
	~DeathRequest();

	DeathRequest(DeathRequest const&);
	DeathRequest& operator=(DeathRequest const&);

public:
	Protocol			&serialize(Protocol &) const;
	Protocol			&unserialize(Protocol &);
	ARequest			*clone() const;

public:
	Ruint16				ID() const;
	void				ID(Ruint16 id);

private:
	Ruint16				_id;
};

