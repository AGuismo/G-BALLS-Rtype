#pragma once

#include	<map>
#include	<list>
#include	"Position.hh"
#include	"Entity.hh"
#include	"IReferee.hh"
#include	"Scenario.hh"

class Player;

class Referee: public IReferee
{
public:
	typedef std::map<unsigned short, Entity *>	objects_map_type;

public:
	Referee(const Scenario &scenario = Scenario(), unsigned short playerID = 0);
	~Referee();

	bool		acceptMove(unsigned short id, const Position &pos);
	bool		acceptFire(unsigned short id, std::vector<Missile> &createdMissiles);

	void		loadScenario(const Scenario &scenario, unsigned short playerID);
	void		update();

	void		sendRequest(/* Add network here */); // Send request to the server (acceptMove + acceptFire)

	unsigned short	uniqueID();

public:
	const objects_map_type	&getMap() const;

	void					setMyPlayer(unsigned short playerID);
	const Player			&getMyPlayer() const;

private:
	void		loadScenario(const Scenario &scenario);

private:
	void		pushRequest(); // Add data from MainReferee (server) => acceptMove and acceptFire calls

private:
	objects_map_type	_objects;
	unsigned short		_playerID;
	Scenario			_scenario;
	unsigned short		_incrementalID;
	// List of request here...
};

