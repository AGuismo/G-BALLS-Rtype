#include	"ObjectMoverStraight.hh"

ObjectMoverStraight::ObjectMoverStraight(const Entity &e, const Animation &a):
ObjectMover(e, a)
{

}

ObjectMoverStraight::ObjectMoverStraight()
{

}

ObjectMoverStraight::~ObjectMoverStraight()
{

}

ObjectMoverStraight::ObjectMoverStraight(const ObjectMoverStraight &src):
ObjectMover(src)
{

}

ObjectMoverStraight	&ObjectMoverStraight::operator=(const ObjectMoverStraight &src)
{
	if (&src != this)
	{
		ObjectMover::operator=(src);
	}
	return (*this);
}

void			ObjectMoverStraight::update()
{
	if (!_isMoving)
	{
		onMove(_entity.getPosition().direction());
	}
	else
	{
		_nextMove = _entity.getPosition().direction();
		_isNextMoveAvailable = true;
	}
	ObjectMover::update();
}