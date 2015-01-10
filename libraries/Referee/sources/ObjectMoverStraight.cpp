#include	"ObjectMoverStraight.hh"

ObjectMoverStraight::ObjectMoverStraight(const Entity &e):
ObjectMover(e)
{
	_direction = e.getPosition().direction;
}

ObjectMoverStraight::ObjectMoverStraight()
{

}

ObjectMoverStraight::~ObjectMoverStraight()
{

}

ObjectMoverStraight::ObjectMoverStraight(const ObjectMoverStraight &src):
ObjectMover(src), _direction(src._direction)
{

}

ObjectMoverStraight	&ObjectMoverStraight::operator=(const ObjectMoverStraight &src)
{
	if (&src != this)
	{
		ObjectMover::operator=(src);
		_direction = src._direction;
	}
	return (*this);
}

bool			ObjectMoverStraight::update()
{
	if (!_isMoving)
	{
		onMove(_direction);
	}
	else
	{
		_nextMove = _direction;
		_isNextMoveAvailable = true;
	}
	return (ObjectMover::update());
}