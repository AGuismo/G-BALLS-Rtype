#pragma once

#include	<set>
#include	<map>
#include	<list>
#include	"types.hh"
#include	"Position.hh"
#include	"Entity.hh"
#include	"Scenario.hh"
#include	"Clock.hh"

class Player;
class ObjectMover;

class MainReferee
{
  struct	InternalPlayerSystem
  {
    Player			*entity;
    ObjectMover			*move;
    Clock			fireLock;
    Clock			moveLock;
  };

  typedef bool(*mover_comp_fn)(const ObjectMover *, const ObjectMover *);
  typedef std::set<ObjectMover *, mover_comp_fn>		mover_set_type;
  typedef std::map<unsigned short, InternalPlayerSystem>	players_map_type;


public:
  static const float	FIRE_LOCK_TIME;
  static const float	MOVE_LOCK_TIME;
  typedef bool(*entity_comp_fn)(const Entity *, const Entity *);
  typedef std::set<Entity *, entity_comp_fn>	entity_set_type;

public:
  MainReferee();
  MainReferee(const Scenario &scenario);
  ~MainReferee();

  bool		acceptMove(unsigned short playerID, Position::dir direction);
  bool		acceptFire(unsigned short playerID);

  void		loadScenario(const Scenario &scenario, unsigned short playerID);
  void		update(std::vector<unsigned short> &deadPlayers);

  unsigned short	uniqueID();

public:
  const entity_set_type	&getMap() const;
  game::Stamp		getStamp() const;

private:
  void		addEntity(Entity *e);
  void		delEntity(unsigned short id);

  static bool	entitiesComp(const Entity *lhs, const Entity *rhs);
  static bool	entityMoveComp(const ObjectMover *lhs, const ObjectMover *rhs);

  void		loadScenario(const Scenario &scenario);
  void		fire(unsigned short playerID);

  void		updateMoves(std::vector<unsigned short> &moved);
  void		checkCollisions(const std::vector<unsigned short> &moved, std::vector<unsigned short>	&toDelete);
  void		checkOutsideMap(const std::vector<unsigned short> &moved, std::vector<unsigned short>	&toDelete);

  static bool	isOutsideMap(const Entity &object, unsigned short mapHeight, unsigned short mapWidth);
  static bool	isCollision(const Entity &object1, const Entity &object2);

private:
  entity_set_type		_entities;
  mover_set_type		_entityMoves;
  players_map_type		_players;
  Scenario			_scenario;
  unsigned short		_incrementalID;
  game::Stamp			_stamp;

  // List of request here...
};

