#pragma once

#include	<set>
#include	<list>
#include	<map>
#include	"Position.hh"
#include	"Entity.hh"
#include	"Scenario.hh"
#include	"Clock.hh"
#include	"types.hh"

class Player;
class Missile;
class ObjectMover;
class ARequest;

class Referee
{
  typedef bool(*mover_comp_fn)(const ObjectMover *, const ObjectMover *);
  typedef std::set<ObjectMover *, mover_comp_fn>	mover_set_type;
  typedef void	(Referee::*request_fn)(const ARequest &);
  typedef std::map<requestCode::CodeID, request_fn> request_callback_map_type;
  typedef std::list<ARequest *>	request_list_type;

public:
  static const float	FIRE_LOCK_TIME;
  static const float	MOVE_LOCK_TIME;
  typedef bool(*entity_comp_fn)(const Entity *, const Entity *);
  typedef std::set<Entity *, entity_comp_fn>	entity_set_type;
  typedef std::list<Missile>					missile_list_type;

public:
	Referee();
  ~Referee();

  bool		acceptMove(Position::dir direction);
  bool		acceptFire();

  void		update(std::vector<unsigned short> &toDelete);

  void		sendRequestToServer(/* Add network here */); // Send request to the server (acceptMove + acceptFire)
  void		recvRequestFromServer(const ARequest &);

  unsigned short	uniqueID();

public:
  const entity_set_type	&getMap() const;
  const Player			&getMyPlayer() const;
  void					setPlayerID(requestCode::SessionID playerID);
  bool					playerInformations(Player &myPlayer, missile_list_type &associatedMissiles) const; // TODO: Bonus list

private:

	void	executeRequestFromServer();
	void	request_command_elem(const ARequest &elem);
	void	request_command_death(const ARequest &death);

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
  static float	distance(const Position &a, const Position &b);

private:
  entity_set_type		_entities;
  mover_set_type		_entityMoves;
  Scenario			_scenario;
  unsigned short		_incrementalID;
  struct
  {
	requestCode::SessionID	id;
    Player			*entity;
    ObjectMover		*move;
    Clock			fireLock;
    Clock			moveLock;
  }					_player;

  request_list_type			_requestsFromServer;
  request_callback_map_type	_requestCommands;

  // List of request here...
};

