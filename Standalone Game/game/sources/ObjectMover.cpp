#include	<math.h>
#include	<iostream>
#include	"ObjectMover.hh"

static const float	SQRT_2 = sqrtf(2.0f);
const float			ObjectMover::DEFAULT_MOVEMENT_DURATION = 0.25f;

ObjectMover::ObjectMover(const Entity &entity, const Animation &anim, float movementDuration) :
_entity(entity), _animations(anim), _isMoving(false), _isNextMoveAvailable(false), _moveDuration(movementDuration)
{
	_position.current = _position.previous = _position.next = sf::Vector2f(entity.getPosition().x(), entity.getPosition().y());
	_movement.endTimer = 0.f;
}

ObjectMover::ObjectMover():
_isMoving(false), _isNextMoveAvailable(false), _moveDuration(DEFAULT_MOVEMENT_DURATION)
{
	_movement.endTimer = 0.f;
}

ObjectMover::~ObjectMover()
{
}

ObjectMover::ObjectMover(const ObjectMover &src):
_entity(src._entity), _animations(src._animations), _moveDuration(src._moveDuration),
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
		_entity = src._entity;
		_animations = src._animations;
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

Entity	&ObjectMover::getEntity()
{
	return (_entity);
}

Animation	&ObjectMover::getAnimation()
{
	return (_animations);
}

const sf::Vector2f	&ObjectMover::getPreviousPos() const
{
	return (_position.previous);
}

const sf::Vector2f	&ObjectMover::getCurrentPos() const
{
	return (_position.current);
}

const sf::Vector2f	&ObjectMover::getNextPos() const
{
	return (_position.next);
}

void			ObjectMover::onMove(Position::dir direction)
{
	if (_entity.isMoveable())
	{
		if (!_isMoving)
		{
			sf::Vector2f	posOffset(0.f, 0.f);

			if (direction == Position::NORTH)
				posOffset.y -= _entity.speed();
			else if (direction == Position::SOUTH)
				posOffset.y += _entity.speed();
			else if (direction == Position::EAST)
				posOffset.x += _entity.speed();
			else if (direction == Position::WEST)
				posOffset.x -= _entity.speed();
			else
			{
				// Crée un triangle rectangle isocèle, avec une hypothénuse de x * sqrt(2) par propriété
				// résolution par thalès ensuite
				float hyp = (_entity.speed() * SQRT_2);
				float realOffset = _entity.speed() * (hyp / 2.f) / hyp; // note: x == y
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
}

void			ObjectMover::update()
{
	if (_position.previous != _position.next && !_isMoving) // start move
	{
		_movement.timer.restart();
		_isMoving = true;
		_movement.endTimer = _moveDuration;
	}
	else if (_isMoving) // move in progress
	{
		sf::Time	totalTime = _movement.timer.getElapsedTime();
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
			}
			else
			{
				_movement.endTimer = 0.0f;
				_isMoving = false;
				_position.current = _position.next;
			}
		}
	}
}