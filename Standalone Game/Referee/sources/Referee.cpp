#if defined(DEBUG)
#include	<stdexcept>
#endif // !DEBUG

#include	"Referee.hh"
#include	"Player.hh"
#include	"Scenario.hh"

const float	Referee::MOVE_LOCK_TIME = 0.25f;
const float	Referee::FIRE_LOCK_TIME = 0.5f;

Referee::Referee(const Scenario &scenario, unsigned short playerID):
_scenario(scenario), _incrementalID(1)
{
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
* - Destroy Objects if necessary - MasterReferee will tell you
* - send to MasterReferee Player Position
*
* The MasterReferee have also:
* - Test if there is collision
* - Apply actions if collision
*
*/
void		Referee::update() 
{

}

/* When protocol will be restored */
void		Referee::sendRequest()
{

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
	if (_objects.find(_incrementalID) != _objects.end())
	{
		++_incrementalID;
		return (uniqueID());
	}
	return (_incrementalID++);
}
