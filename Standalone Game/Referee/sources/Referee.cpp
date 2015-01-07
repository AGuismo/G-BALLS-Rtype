#if defined(DEBUG)
#include	<stdexcept>
#endif // !DEBUG

#include	"Mob.hh" // DEBUG
#include	"Rect.hpp"
#include	"Referee.hh"
#include	"Player.hh"
#include	"Scenario.hh"

const float	Referee::MOVE_LOCK_TIME = 0.25f;
const float	Referee::FIRE_LOCK_TIME = 0.5f;

Referee::Referee(const Scenario &scenario, unsigned short playerID):
_scenario(scenario), _incrementalID(1)
{
	_objects[5] = new Mob(5, Position(800, 500, Position::WEST), 1);
}

Referee::~Referee()
{
	while (!_objects.empty())
	{
		delete _objects.begin()->second;
		_objects.erase(_objects.begin()->first);
	}
}

void				Referee::fire(std::vector<Missile> &createdMissiles)
{
	Position		missilePos;
	Missile			*missile = new Missile(uniqueID(), missilePos);
	const Player	&me = getMyPlayer();

	missilePos.x(me.getPosition().x() + me.getWidth() + 5);
	missilePos.y(me.getPosition().y() + (me.getHeight() / 2 - missile->getHeight() / 2));
	missilePos.direction(Position::EAST);
	missile->setPosition(missilePos);
	_objects[missile->getID()] = missile;
	createdMissiles.push_back(*missile);
}

bool				Referee::acceptFire(unsigned short id, std::vector<Missile> &createdMissiles) // Fire can only be my player fire in this case
{
	if (_player.fireLock.getElapsedTime().asSeconds() < (FIRE_LOCK_TIME * _scenario.getGameSpeed()))
		return (false);
	_player.fireLock.restart();
	fire(createdMissiles);
	return (true);
}

bool		Referee::acceptMove(unsigned short id, const Position &pos)
{
	if (id == _player.object->getID())
	{
		if (_player.moveLock.getElapsedTime().asSeconds() < (MOVE_LOCK_TIME * _scenario.getGameSpeed()))
			return (false);
		_player.moveLock.restart();
	}
	_objects[id]->setPosition(pos);
	return (true);
}

void		Referee::loadScenario(const Scenario &scenario, unsigned short playerID)
{
	loadScenario(scenario);
	setMyPlayer(playerID);
}

void		Referee::loadScenario(const Scenario &scenario)
{
	bool	changed = true;

	_scenario = scenario;
	while (changed)
	{
		changed = false;
		for (objects_map_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
		{
			if (it->second->getType().desc.maj == Entity::PLAYER)
			{
				_objects.erase(it);
				changed = true;
				break;
			}
		}
	}
	for (std::vector<Player>::const_iterator it = scenario.getPlayers().begin();
		it != scenario.getPlayers().end(); ++it)
		_objects[it->getID()] = new Player(*it);
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
	unsigned short	mapHeight, mapWidth;
	// GetRequests...

	toDelete.clear();
	_scenario.getMapSize(mapHeight, mapWidth);
	for (objects_map_type::iterator it = _objects.begin(); it != _objects.end(); ++it) // Obj vs Map
	{
		if (Referee::isOutsideMap(*it->second, mapHeight, mapWidth))
			toDelete.push_back(it->first);
	}
	for (std::vector<unsigned short>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
	{
		if (*it == _player.object->getID())
			continue; // don't delete it
		_objects.erase(*it);
	}

	for (objects_map_type::iterator it = _objects.begin(); it != _objects.end(); ++it) // Obj vs Obj
	{
		for (objects_map_type::iterator it2 = _objects.begin(); it2 != _objects.end(); ++it2) // Obj vs Obj
		{
			if (it->first != it2->first && Referee::isCollision(*it->second, *it2->second))
			{
				toDelete.push_back(it->first);
				toDelete.push_back(it2->first);
			}
		}
	}
	for (std::vector<unsigned short>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
	{
		if (*it == _player.object->getID())
			continue; // don't delete it
		_objects.erase(*it);
	}
	// SendPlayerPosition to MasterReferee...
}

/* When protocol will be restored */
void		Referee::sendRequest()
{

}

bool		Referee::isOutsideMap(const Entity &object, unsigned short mapHeight, unsigned short mapWidth)
{
	return (object.getPosition().x() + object.getWidth() > mapWidth || object.getPosition().y() + object.getHeight() > mapHeight);
}

bool		Referee::isCollision(const Entity &object1, const Entity &object2)
{
	Rect<>	obj1(object1.getPosition().x(), object1.getPosition().y(), object1.getWidth(), object1.getHeight());
	Rect<>	obj2(object2.getPosition().x(), object2.getPosition().y(), object2.getWidth(), object2.getHeight());

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

const Referee::objects_map_type	&Referee::getMap() const
{
	return (_objects);
}

void			Referee::setMyPlayer(unsigned short playerID)
{
#if defined(DEBUG)
	if (_objects.find(playerID) == _objects.end())
		throw std::runtime_error("Referee::setMyPlayer(): Invalid playerID");
#endif
	_player.object = dynamic_cast<Player *>(_objects[playerID]);
}

#include	<typeinfo>

const Player	&Referee::getMyPlayer() const
{
	return (*_player.object);
}

unsigned short	Referee::uniqueID()
{
	while (_objects.find(_incrementalID) != _objects.end())
		++_incrementalID;
	return (_incrementalID++);
}
