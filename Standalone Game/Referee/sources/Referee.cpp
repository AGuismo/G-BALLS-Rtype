#if defined(DEBUG)
#include	<stdexcept>
#endif // !DEBUG

#include	"Referee.hh"
#include	"Player.hh"
#include	"Scenario.hh"

Referee::Referee(const Scenario &scenario, unsigned short playerID):
_playerID(playerID), _scenario(scenario), _incrementalID(1)
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

bool		Referee::acceptFire(unsigned short id, std::vector<Missile> &createdMissiles) // Fire can only be my player fire in this case
{
	Missile	*missile = new Missile(uniqueID(), Position(500, 500, Position::EAST));

	_objects[missile->getID()] = missile;
	createdMissiles.push_back(*missile);
	return (true);
}

bool		Referee::acceptMove(unsigned short id, const Position &pos)
{
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
	_playerID = playerID;
}

#include	<typeinfo>

const Player	&Referee::getMyPlayer() const
{
	return (dynamic_cast<const Player &>(*_objects.find(_playerID)->second));
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
