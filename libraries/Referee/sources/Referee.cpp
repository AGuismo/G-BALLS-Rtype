#if defined(DEBUG)
#include	<stdexcept>
#endif // !DEBUG

#include	"Mob.hh" // DEBUG
#include	"Missile.hh"
#include	"Rect.hpp"
#include	"Referee.hh"
#include	"Player.hh"
#include	"Scenario.hh"
#include	"ObjectMover.hh"
#include	"EntityFactory.hh"

#include	"AGameRequest.hh"
#include	"ElemRequest.hh"
#include	"LeaveRequest.hh"
#include	"DeathRequest.hh"

const float	Referee::MOVE_LOCK_TIME = 0.25f;
const float	Referee::FIRE_LOCK_TIME = 0.5f;

Referee::Referee() :
_entities(&entitiesComp), _entityMoves(&entityMoveComp), _incrementalID(1)
{
	_player.entity = 0;

	_requestCommands[requestCode::game::ELEM] = &Referee::request_command_elem;
	_requestCommands[requestCode::game::DEATH] = &Referee::request_command_death;
}

//Referee::Referee(const Scenario &scenario, unsigned short playerID):
//  _entities(&entitiesComp), _entityMoves(&entityMoveComp), _incrementalID(1)
//{
//  loadScenario(scenario);
  //setMyPlayer(playerID);
//}

Referee::~Referee()
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

void				Referee::fire()
{
  Position		missilePos;
  Missile		*missile = new Missile(uniqueID(), missilePos);
  const Player	&me = getMyPlayer();

  missilePos.x = me.getPosition().x + me.getWidth() + 5;
  missilePos.y = me.getPosition().y + (me.getHeight() / 2 - missile->getHeight() / 2);
  missilePos.direction = Position::EAST;
  missile->setPosition(missilePos);
  addEntity(missile);
}

bool				Referee::acceptFire() // Fire can only be my player fire in this case
{
	if (_player.entity == 0)
		return (false);
  if (_player.fireLock.getElapsedTime().asSeconds() < (FIRE_LOCK_TIME * _scenario.getGameSpeed()))
    return (false);
  _player.fireLock.restart();
  fire();
  return (true);
}

bool		Referee::acceptMove(Position::dir direction)
{
	if (_player.entity == 0)
		return (false);
	if (_player.moveLock.getElapsedTime().asSeconds() < (MOVE_LOCK_TIME * _scenario.getGameSpeed()))
  {
    _player.move->onMove(direction);
    return (false);
  }
  _player.moveLock.restart();
  _player.move->onMove(direction);
  _player.entity->setPosition(_player.move->getNextPos());
  return (true);
}

//void		Referee::loadScenario(const Scenario &scenario, unsigned short playerID)
//{
//  loadScenario(scenario);
//  setMyPlayer(playerID);
//}

void		Referee::loadScenario(const Scenario &scenario)
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
    addEntity(new Player(*it));
}

void	Referee::executeRequestFromServer()
{
	for (request_list_type::iterator it = _requestsFromServer.begin();
		it != _requestsFromServer.end(); ++it)
	{
		request_callback_map_type::iterator	command = _requestCommands.find((*it)->code());

		if (command != _requestCommands.end())
			(this->*(command->second))(**it);
	}
	_requestsFromServer.clear();
}

void	Referee::request_command_elem(const ARequest &base)
{
	const ElemRequest	&elem = dynamic_cast<const ElemRequest &>(base);
	EntityComparer		comparer(elem.ID());
	entity_set_type::iterator	it = _entities.find(&comparer);

	if (it == _entities.end())
		addEntity(elem.entity()->copy());
	else
	{
		ObjectMoverComparer			moveComparer(elem.ID());
		mover_set_type::iterator	itMover = _entityMoves.find(&moveComparer);
		
		if ((*itMover)->getLastUpdate() < elem.Stamp())
		{
			(*itMover)->forcePosition(elem.entity()->getPosition());
			(*itMover)->setLastUpdate(elem.Stamp());
			// TODO: Move Object
		}
	}

}

void	Referee::request_command_death(const ARequest &base)
{
	const ElemRequest	&elem = dynamic_cast<const ElemRequest &>(base);
	EntityComparer		comparer(elem.ID());

	if (_entities.find(&comparer) == _entities.end())
		delEntity(elem.ID());
}


void	Referee::addEntity(Entity *e)
{
  _entities.insert(e);
  std::pair<mover_set_type::iterator, bool> result = _entityMoves.insert(EntityFactory::getInstance().createObject(e->getType(), e->getID(), e->getPosition()));
  if (_player.entity == 0 && result.second && e->getID() == _player.id)
  {
	  _player.entity = dynamic_cast<Player *>(e);
	  _player.move = *result.first;
  }
}

void	Referee::delEntity(unsigned short id)
{
  EntityComparer				entity(id);
  entity_set_type::iterator	itEntity = _entities.find(&entity);

  ObjectMoverComparer			move(id);
  mover_set_type::iterator	itMover = _entityMoves.find(&move);

  delete *itEntity;
  delete *itMover;
  _entityMoves.erase(itMover);
  _entities.erase(itEntity);
}

void	Referee::updateMoves(std::vector<unsigned short> &moved)
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

void	Referee::checkOutsideMap(const std::vector<unsigned short> &moved, std::vector<unsigned short> &toDelete)
{
  unsigned short				mapHeight, mapWidth;

  _scenario.getMapSize(mapHeight, mapWidth);
  for (std::vector<unsigned short>::const_iterator it = moved.begin(); it != moved.end(); ++it)
  {
    EntityComparer	c(*it);
    Entity			*current = *_entities.find(&c);

    if (Referee::isOutsideMap(*current, mapHeight, mapWidth))
      toDelete.push_back(*it);
  }
}

void	Referee::checkCollisions(const std::vector<unsigned short> &moved, std::vector<unsigned short> &toDelete)
{
  for (std::vector<unsigned short>::const_iterator it = moved.begin(); it != moved.end(); ++it)
  {
    EntityComparer	c(*it);
    Entity			*obj1 = *_entities.find(&c);

    for (entity_set_type::iterator it2 = _entities.begin(); it2 != _entities.end(); ++it2) // Obj vs Obj
    {
      Entity		*obj2 = *it2;

      if (obj1 != obj2 && Referee::isCollision(*obj1, *obj2))
      {
	toDelete.push_back(*it);
	break;
      }
    }
  }
}

/*
 * Purpose:
 * - Get requests from MasterReferee to update map
 * - Destroy Objects if necessary - MasterReferee will tell you or object outside map.
 * - send to MasterReferee Player Position
 *
 * The MasterReferee have also (that Rerefee doesn't have):
 * - Test if there is collision
 * - Apply actions if collision
 *
 */
void		Referee::update(std::vector<unsigned short>	&toDelete)
{
  std::vector<unsigned short>	moved;
  // GetRequests...

  toDelete.clear();
  executeRequestFromServer();
  updateMoves(moved);
  checkOutsideMap(moved, toDelete);
  checkCollisions(moved, toDelete);

  for (std::vector<unsigned short>::const_iterator it = toDelete.begin(); it != toDelete.end(); ++it)
  {
    if (*it == _player.entity->getID())
      continue;
    delEntity(*it);
  }
  //for (mover_set_type::iterator it = _entityMoves.begin(); it != _entityMoves.end(); ++it) // Obj vs Map
  //{
  //	if (Referee::isOutsideMap(*(*it), mapHeight, mapWidth))
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
  //		if (it->first != it2->first && Referee::isCollision(*it->second, *it2->second))
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
  // SendPlayerPosition to MasterReferee...
}

bool		Referee::playerInformations(Player &myPlayer, missile_list_type &associatedMissiles) const
{
	if (_player.entity == 0)
		return (false);
	myPlayer = getMyPlayer();
	associatedMissiles.clear();
	return (true);
}

void		Referee::recvRequestFromServer(const ARequest &req)
{
	_requestsFromServer.push_back(req.clone());
}

bool		Referee::isOutsideMap(const Entity &object, unsigned short mapHeight, unsigned short mapWidth)
{
  return (object.getPosition().x + object.getWidth() > mapWidth || object.getPosition().y + object.getHeight() > mapHeight);
}

bool		Referee::isCollision(const Entity &object1, const Entity &object2)
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

bool	Referee::entitiesComp(const Entity *lhs, const Entity *rhs)
{
  return (lhs->getID() < rhs->getID());
}

bool	Referee::entityMoveComp(const ObjectMover *lhs, const ObjectMover *rhs)
{
  return (lhs->getObjectID() < rhs->getObjectID());
}


const Referee::entity_set_type	&Referee::getMap() const
{
  return (_entities);
}

//void			Referee::setMyPlayer(unsigned short playerID)
//{
//  ObjectMoverComparer	moverComp(playerID);
//  EntityComparer		entityComp(playerID);
//#if defined(DEBUG)
//  if (_entities.find(&entityComp) == _entities.end())
//    throw std::runtime_error("Referee::setMyPlayer(): Invalid playerID");
//#endif
//  _player.entity = dynamic_cast<Player *>(*_entities.find(&entityComp));
//  _player.move = *_entityMoves.find(&moverComp);
//}

void			Referee::setPlayerID(requestCode::SessionID playerID)
{
	_player.id = playerID;
}

const Player	&Referee::getMyPlayer() const
{
  return (*_player.entity);
}

unsigned short	Referee::uniqueID()
{
  EntityComparer	c(_incrementalID);

  while (_entities.find(&c) != _entities.end())
  {
    ++_incrementalID;
    c.id(_incrementalID);
  }
  return (_incrementalID++);
}