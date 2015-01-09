#pragma once

#include	<set>
#include	<list>
#include	"Position.hh"
#include	"Entity.hh"
#include	"IReferee.hh"
#include	"Scenario.hh"
#include	"Clock.hh"

class Player;
class ObjectMover;

class Referee
{
	typedef bool(*mover_comp_fn)(const ObjectMover *, const ObjectMover *);
	typedef std::set<ObjectMover *, mover_comp_fn>	mover_set_type;

public:
	static const float	FIRE_LOCK_TIME;
	static const float	MOVE_LOCK_TIME;
	typedef bool(*entity_comp_fn)(const Entity *, const Entity *);
	typedef std::set<Entity *, entity_comp_fn>	entity_set_type;

public:
	Referee(const Scenario &scenario = Scenario(), unsigned short playerID = 0);
	~Referee();

	bool		acceptMove(Position::dir direction);
	bool		acceptFire();

	void		loadScenario(const Scenario &scenario, unsigned short playerID);
	void		update(std::vector<unsigned short> &toDelete);

	void		sendRequest(/* Add network here */); // Send request to the server (acceptMove + acceptFire)

	unsigned short	uniqueID();

public:
	const entity_set_type	&getMap() const;

	void					setMyPlayer(unsigned short playerID);
	const Player			&getMyPlayer() const;

private:
	void		addEntity(Entity *e);
	void		delEntity(unsigned short id);

	static bool	entitiesComp(const Entity *lhs, const Entity *rhs);
	static bool	entityMoveComp(const ObjectMover *lhs, const ObjectMover *rhs);

	void		loadScenario(const Scenario &scenario);
	void		fire();

	void		updateMoves(std::vector<unsigned short> &moved);
	void		checkCollisions(const std::vector<unsigned short> &moved, std::vector<unsigned short>	&toDelete);
	void		checkOutsideMap(const std::vector<unsigned short> &moved, std::vector<unsigned short>	&toDelete);

	static bool	isOutsideMap(const Entity &object, unsigned short mapHeight, unsigned short mapWidth);
	static bool	isCollision(const Entity &object1, const Entity &object2);

private:
	void		pushRequest(); // Add data from MainReferee (server) => acceptMove and acceptFire calls

private:
	entity_set_type		_entities;
	mover_set_type		_entityMoves;
	Scenario			_scenario;
	unsigned short		_incrementalID;
	struct
	{
		Player			*entity;
		ObjectMover		*move;
		Clock			fireLock;
		Clock			moveLock;
	}					_player;


	// List of request here...
};

