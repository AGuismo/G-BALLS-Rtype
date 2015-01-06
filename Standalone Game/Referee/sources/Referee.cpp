#include	"Referee.hh"
#include	"Player.hh"

Referee::Referee()
{
}


Referee::~Referee()
{
}

bool		Referee::acceptFire(unsigned short id)
{
	return (true);
}

bool		Referee::acceptMove(unsigned short id, const Position &pos)
{
	return (true);
}

/*
* Purpose:
* - Test if there is collision
* - Apply actions if collision
* - Get requests from MasterReferee to update map
* - Destroy Objects if necessary
* - send to MasterReferee Player Position
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

const Player	&Referee::getMyPlayer() const
{
	return (dynamic_cast<const Player &>(_objects.at(_playerID)));
}