#pragma once

#include	<map>
#include	<list>
#include	"Position.hh"
#include	"Entity.hh"

class Player;

class Referee
{
public:
	typedef std::map<unsigned short, Entity>	objects_map_type;

public:
	Referee();
	~Referee();

	bool		acceptMove(unsigned short id, const Position &pos);
	bool		acceptFire(unsigned short id);

	void		update();
	void		sendRequest(/* Add network here */); // Send request to the server (acceptMove + acceptFire)

public:
	const objects_map_type	&getMap() const;
	const Player			&getMyPlayer() const;

private:
	void		pushRequest(); // Add data from MainReferee (server) => acceptMove and acceptFire calls

private:
	objects_map_type	_objects;
	unsigned short		_playerID;
	// List of request here...
};

