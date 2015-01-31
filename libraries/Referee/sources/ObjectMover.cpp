#include	<math.h>
#include	<iostream>
#include	"ObjectMover.hh"
#include	"Referee.hh"
#include	"Time.hh"

static const float	SQRT_2 = sqrtf(2.0f);
const float			ObjectMover::DEFAULT_MOVEMENT_DURATION = 0.25f;

ObjectMover::ObjectMover(const Entity &entity, float movementDuration) :
  _objectID(entity.getID()), _speed(entity.speed()), _moveDuration(movementDuration),_isMoving(false), _isNextMoveAvailable(false)
{
	_position.current = _position.previous = _position.next = entity.getPosition();
	_movement.endTimer = 0.f;
}

ObjectMover::ObjectMover():
  _objectID(0), _moveDuration(DEFAULT_MOVEMENT_DURATION), _isMoving(false), _isNextMoveAvailable(false)
{
	_movement.endTimer = 0.f;
}

ObjectMover::~ObjectMover()
{
}

ObjectMover::ObjectMover(const ObjectMover &src):
_objectID(src._objectID), _speed(src._speed), _moveDuration(src._moveDuration),
_isMoving(src._isMoving), _isNextMoveAvailable(src._isNextMoveAvailable), _nextMove(src._nextMove)
{
	_movement.timer = src._movement.timer;
	_movement.endTimer = src._movement.endTimer;
	_position.previous = src._position.previous;
	_position.current = src._position.current;
	_position.next = src._position.next;
}

ObjectMover	&ObjectMover::operator=(const ObjectMover &src)
{
	if (&src != this)
	{
		_objectID = src._objectID;
		_speed = src._speed;
		//_animations = src._animations;
		_position.previous = src._position.previous;
		_position.current = src._position.current;
		_position.next = src._position.next;
		_movement.timer = src._movement.timer;
		_movement.endTimer = src._movement.endTimer;
		_moveDuration = src._moveDuration;
		_isMoving = src._isMoving;
		_isNextMoveAvailable = src._isNextMoveAvailable;
		_nextMove = src._nextMove;
	}
	return (*this);
}

void	ObjectMover::changeSpeed(short speed)
{
	_speed = speed;
}

void		ObjectMover::forcePosition(const Position &currentPos)
{
	_position.previous = _position.current = _position.next = currentPos;
	_isMoving = false;
	_isNextMoveAvailable = false;
}

//Animation	&ObjectMover::getAnimation()
//{
//	return (_animations);
//}

const Position	&ObjectMover::getPreviousPos() const
{
	return (_position.previous);
}

const Position	&ObjectMover::getCurrentPos() const
{
	return (_position.current);
}

const Position	&ObjectMover::getNextPos() const
{
	return (_position.next);
}

unsigned short	ObjectMover::getObjectID() const
{
	return (_objectID);
}

void			ObjectMover::onMove(Position::dir direction)
{
	if (!_isMoving)
	{
		Position	posOffset(0, 0);

		if (direction == Position::NORTH)
			posOffset.y -= _speed;
		else if (direction == Position::SOUTH)
			posOffset.y += _speed;
		else if (direction == Position::EAST)
			posOffset.x += _speed;
		else if (direction == Position::WEST)
			posOffset.x -= _speed;
		else
		{
			// Crée un triangle rectangle isocèle, avec une hypothénuse de x * sqrt(2) par propriété
			// résolution par thalès ensuite
			float hyp = (_speed * SQRT_2);
			float realOffset = _speed * (hyp / 2.f) / hyp; // note: x == y
			if (direction == Position::NORTH_EAST || direction == Position::SOUTH_EAST)
				posOffset.x += realOffset;
			else
				posOffset.x -= realOffset;
			if (direction == Position::SOUTH_EAST || direction == Position::SOUTH_WEST)
				posOffset.y += realOffset;
			else
				posOffset.y -= realOffset;
		}
		_position.next += posOffset;
		_movement.endTimer += _moveDuration;
	}
	else
	{
		_isNextMoveAvailable = true;
		_nextMove = direction;
	}
}

bool			ObjectMover::update()
{
	if (_position.previous != _position.next && !_isMoving) // start move
	{
		_movement.timer.restart();
		_isMoving = true;
		_movement.endTimer = _moveDuration;
		return (true);
	}
	else if (_isMoving) // move in progress
	{
		Time		totalTime = _movement.timer.getElapsedTime();
		float		progress = totalTime.asSeconds() / _movement.endTimer;

		_position.current.x = _position.previous.x + (_position.next.x - _position.previous.x) * progress;
		_position.current.y = _position.previous.y + (_position.next.y - _position.previous.y) * progress;

		if (totalTime.asSeconds() >= _movement.endTimer) // move finish
		{
			_position.previous = _position.next;
			_isMoving = false;
			if (_isNextMoveAvailable)
			{
				onMove(_nextMove);
				_isNextMoveAvailable = false;
				_isMoving = true;
				_movement.timer.restart();
				_movement.endTimer = _moveDuration;
				return (true);
			}
			else
			{
				_movement.endTimer = 0.0f;
				_isMoving = false;
				_position.current = _position.next;
				return (false);
			}
		}
	}
	return (false);
}
