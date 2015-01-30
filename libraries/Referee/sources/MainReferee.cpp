#if defined(DEBUG)
#include	<stdexcept>
#endif // !DEBUG

#include	"Mob.hh" // DEBUG
#include	"Missile.hh"
#include	"Rect.hpp"
#include	"MainReferee.hh"
#include	"Player.hh"
#include	"Scenario.hh"
#include	"ObjectMover.hh"
#include	"EntityFactory.hh"

const float	MainReferee::MOVE_LOCK_TIME = 0.25f;
const float	MainReferee::FIRE_LOCK_TIME = 0.5f;

MainReferee::MainReferee():
  _entities(&entitiesComp), _entityMoves(&entityMoveComp), _incrementalID(1), _stamp(1)
{
}

MainReferee::MainReferee(const Scenario &scenario):
  _entities(&entitiesComp), _entityMoves(&entityMoveComp), _incrementalID(1), _stamp(1)
{
  loadScenario(scenario);
}

MainReferee::~MainReferee()
{
  while (!_entities.empty())
  {
    delete *_entities.begin();
    _entities.erase(_entities.begin());
  }
  while (!_entityMoves.empty())
  {
    delete *_entityMoves.begin();
    _entityMoves.erase(_entityMoves.begin());
  }
}

void				MainReferee::fire(unsigned short playerID)
{
  Position		missilePos;
  Missile		*missile = new Missile(uniqueID(), missilePos);
  const Player		*me = _players[playerID].entity;

  missilePos.x = me->getPosition().x + me->getWidth() + 5;
  missilePos.y = me->getPosition().y + (me->getHeight() / 2 - missile->getHeight() / 2);
  missilePos.direction = Position::EAST;
  missile->setPosition(missilePos);
  addEntity(missile);
}

bool				MainReferee::acceptFire(unsigned short playerID)
{
  InternalPlayerSystem		player = _players[playerID];

  if (player.fireLock.getElapsedTime().asSeconds() < (FIRE_LOCK_TIME * _scenario.getGameSpeed()))
    return (false);
  player.fireLock.restart();
  fire(playerID);
  return (true);
}

bool		MainReferee::acceptMove(unsigned short playerID, Position::dir direction)
{
  InternalPlayerSystem		player = _players[playerID];

  if (player.moveLock.getElapsedTime().asSeconds() < (MOVE_LOCK_TIME * _scenario.getGameSpeed()))
  {
    player.move->onMove(direction);
    return (false);
  }
  player.moveLock.restart();
  player.move->onMove(direction);
  return (true);
}

bool		MainReferee::acceptPlayerPosition(const Player &currentPlayer)
{
  InternalPlayerSystem		player = _players[currentPlayer.getID()];

  if (player.moveLock.getElapsedTime().asSeconds() < (MOVE_LOCK_TIME * _scenario.getGameSpeed()))
  {
    player.entity->setPosition(currentPlayer.getPosition());
    // TODO: Add PlayerMove
  }
  return (true);
}

bool		MainReferee::acceptFire(const Missile &missile)
{
  EntityComparer		entity(missile.getID());
  entity_set_type::iterator	itEntity = _entities.find(&entity);

  if (itEntity == _entities.end())
  {
    addEntity(missile.copy()); // TODO: check If he can Fire or not
  }
  return (true);
}

void		MainReferee::loadScenario(const Scenario &scenario)
{
  _scenario = scenario;
  while (!_entities.empty())
  {
    delete *_entities.begin();
    _entities.erase(_entities.begin());
  }
  while (!_entityMoves.empty())
  {
    delete *_entityMoves.begin();
    _entityMoves.erase(_entityMoves.begin());
  }
  for (std::vector<Player>::const_iterator it = scenario.getPlayers().begin();
       it != scenario.getPlayers().end(); ++it)
  {
    InternalPlayerSystem	internalPlayer;
    Player			*player = new Player(*it);
    ObjectMoverComparer		move(it->getID());

    addEntity(player);
    mover_set_type::iterator	itMover = _entityMoves.find(&move);


    internalPlayer.entity = player;
    internalPlayer.move = *itMover;

    _players[it->getID()] = internalPlayer;
  }
  addEntity(new Mob(5, Position(800, 500, Position::WEST), 1)); // DEBUG
}

void	MainReferee::addEntity(Entity *e)
{
  _entities.insert(e);
  _entityMoves.insert(EntityFactory::getInstance().createObject(e->getType(), e->getID(), e->getPosition()));
}

void	MainReferee::delEntity(unsigned short id)
{
  EntityComparer		entity(id);
  entity_set_type::iterator	itEntity = _entities.find(&entity);

  ObjectMoverComparer		move(id);
  mover_set_type::iterator	itMover = _entityMoves.find(&move);

  delete *itEntity;
  delete *itMover;
  _entityMoves.erase(itMover);
  _entities.erase(itEntity);
}

void	MainReferee::updateMoves(std::vector<unsigned short> &moved)
{
  for (mover_set_type::iterator it = _entityMoves.begin(); it != _entityMoves.end(); ++it)
  {
    if ((*it)->update())
    {
      EntityComparer	c((*it)->getObjectID());
      Entity			*current = *_entities.find(&c);

      moved.push_back((*it)->getObjectID());
      current->setPosition((*it)->getCurrentPos());
    }
  }
}

void	MainReferee::checkOutsideMap(const std::vector<unsigned short> &moved, std::vector<unsigned short> &toDelete)
{
  unsigned short				mapHeight, mapWidth;

  _scenario.getMapSize(mapHeight, mapWidth);
  for (std::vector<unsigned short>::const_iterator it = moved.begin(); it != moved.end(); ++it)
  {
    EntityComparer	c(*it);
    Entity			*current = *_entities.find(&c);

    if (MainReferee::isOutsideMap(*current, mapHeight, mapWidth))
      toDelete.push_back(*it);
  }
}

void	MainReferee::checkCollisions(const std::vector<unsigned short> &moved, std::vector<unsigned short> &toDelete)
{
  for (std::vector<unsigned short>::const_iterator it = moved.begin(); it != moved.end(); ++it)
  {
    EntityComparer	c(*it);
    Entity			*obj1 = *_entities.find(&c);

    for (entity_set_type::iterator it2 = _entities.begin(); it2 != _entities.end(); ++it2) // Obj vs Obj
    {
      Entity		*obj2 = *it2;

      if (obj1 != obj2 && MainReferee::isCollision(*obj1, *obj2))
      {
	toDelete.push_back(*it);
	break;
      }
    }
  }
}

/*
 * Purpose:
 * - Get requests from MasterMainReferee to update map
 * - Destroy Objects if necessary - MasterMainReferee will tell you or object outside map.
 * - send to MasterMainReferee Player Position
 *
 * The MasterMainReferee have also (that Rerefee doesn't have):
 * - Test if there is collision
 * - Apply actions if collision
 *
 */
void		MainReferee::update(std::vector<unsigned short>	&toDelete)
{
  std::vector<unsigned short>	moved;
  // GetRequests...

  _stamp++;
  toDelete.clear();
  updateMoves(moved);
  checkOutsideMap(moved, toDelete);
  checkCollisions(moved, toDelete);

  for (std::vector<unsigned short>::const_iterator it = toDelete.begin(); it != toDelete.end(); ++it)
  {
    if (_players.find(*it) != _players.end())
      continue;
    delEntity(*it);
  }
  //for (mover_set_type::iterator it = _entityMoves.begin(); it != _entityMoves.end(); ++it) // Obj vs Map
  //{
  //	if (MainReferee::isOutsideMap(*(*it), mapHeight, mapWidth))
  //		toDelete.push_back(it->first);
  //}
  //for (std::vector<unsigned short>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
  //{
  //	if (*it == _player.object->getID())
  //		continue; // don't delete it
  //	_entityMoves.erase(*it);
  //}

  //for (mover_set_type::iterator it = _entityMoves.begin(); it != _entityMoves.end(); ++it) // Obj vs Obj
  //{
  //	for (mover_set_type::iterator it2 = _entityMoves.begin(); it2 != _entityMoves.end(); ++it2) // Obj vs Obj
  //	{
  //		if (it->first != it2->first && MainReferee::isCollision(*it->second, *it2->second))
  //		{
  //			toDelete.push_back(it->first);
  //			toDelete.push_back(it2->first);
  //		}
  //	}
  //}
  //for (std::vector<unsigned short>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
  //{
  //	if (*it == _player.object->getID())
  //		continue; // don't delete it
  //	_objects.erase(*it);
  //}
  // SendPlayerPosition to MasterMainReferee...
}

bool		MainReferee::isOutsideMap(const Entity &object, unsigned short mapHeight, unsigned short mapWidth)
{
  return (object.getPosition().x + object.getWidth() > mapWidth || object.getPosition().y + object.getHeight() > mapHeight);
}

bool		MainReferee::isCollision(const Entity &object1, const Entity &object2)
{
  Rect<>	obj1(object1.getPosition().x, object1.getPosition().y, object1.getWidth(), object1.getHeight());
  Rect<>	obj2(object2.getPosition().x, object2.getPosition().y, object2.getWidth(), object2.getHeight());

  //return NOT(
  //	(Rect1.Bottom < Rect2.Top) OR
  //	(Rect1.Top > Rect2.Bottom) OR
  //	(Rect1.Left > Rect2.Right) OR
  //	(Rect1.Right < Rect2.Left))
  return ((obj1.m_y + obj1.m_height > obj2.m_y) &&
	  (obj1.m_y < obj2.m_y + obj2.m_height) &&
	  (obj1.m_x < obj2.m_x + obj2.m_width) &&
	  (obj1.m_x + obj1.m_width > obj2.m_x));
}

bool	MainReferee::entitiesComp(const Entity *lhs, const Entity *rhs)
{
  return (lhs->getID() < rhs->getID());
}

bool	MainReferee::entityMoveComp(const ObjectMover *lhs, const ObjectMover *rhs)
{
  return (lhs->getObjectID() < rhs->getObjectID());
}


const MainReferee::entity_set_type	&MainReferee::getMap() const
{
  return (_entities);
}

game::Stamp				MainReferee::getStamp() const
{
  return (_stamp);
}

// void			MainReferee::setMyPlayer(unsigned short playerID)
// {
//   ObjectMoverComparer	moverComp(playerID);
//   EntityComparer		entityComp(playerID);
// #if defined(DEBUG)
//   if (_objects.find(playerID) == _objects.end())
//     throw std::runtime_error("MainReferee::setMyPlayer(): Invalid playerID");
// #endif
//   _player.entity = dynamic_cast<Player *>(*_entities.find(&entityComp));
//   _player.move = *_entityMoves.find(&moverComp);
// }

// const Player	&MainReferee::getMyPlayer() const
// {
//   return (*_player.entity);
// }

unsigned short	MainReferee::uniqueID()
{
  EntityComparer	c(_incrementalID);

  while (_entities.find(&c) != _entities.end())
  {
    ++_incrementalID;
    c.id(_incrementalID);
  }
  return (_incrementalID++);
}
