#pragma once

#include	<vector>
#include	"Missile.hh"

class Position;
class Scenario;

class IReferee
{
public:
	enum Difficulty
	{
		EASY,
		MEDIUM,
		HARD
	};

	virtual ~IReferee() {}
	virtual bool	acceptMove(unsigned short id, const Position &pos) = 0;
	virtual bool	acceptFire(unsigned short id, std::vector<Missile> &createdMissiles) = 0;
	virtual void	loadScenario(const Scenario &scenario) = 0;

	virtual void	update() = 0;
	
	virtual unsigned short	uniqueID() = 0;
};
