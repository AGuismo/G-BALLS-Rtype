#include	"ObjectMoverStraight.hh"

ObjectMoverStraight::ObjectMoverStraight(const Entity &e, const Animation &a):
ObjectMover(e, a)
{
	_direction = e.getPosition().direction();
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

void			ObjectMoverStraight::update(Referee &referee)
{
	if (!_isMoving)
	{
		onMove(_direction, referee);
	}
	else
	{
		_nextMove = _direction;
		_isNextMoveAvailable = true;
	}
	ObjectMover::update(referee);
}