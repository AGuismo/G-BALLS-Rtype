#include	<math.h>
#include	"ObjectMover.hh"

static const float SQRT_2 = sqrtf(2.0f);

ObjectMover::ObjectMover(const Entity &entity, const Animation &anim):
_entity(entity), _animations(anim)
{
	_currentPos = _previousPos = _nextPos = sf::Vector2f(entity.getPosition().x(), entity.getPosition().y());
}

ObjectMover::ObjectMover()
{
}

ObjectMover::~ObjectMover()
{
}

ObjectMover::ObjectMover(const ObjectMover &src):
_entity(src._entity), _animations(src._animations), _previousPos(src._previousPos),
_currentPos(src._currentPos), _nextPos(src._nextPos)
{
}

ObjectMover	&ObjectMover::operator=(const ObjectMover &src)
{
	if (&src != this)
	{
		_entity = src._entity;
		_animations = src._animations;
		_previousPos = src._previousPos;
		_currentPos = src._currentPos;
		_nextPos = src._nextPos;
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
	return (_previousPos);
}

const sf::Vector2f	&ObjectMover::getCurrentPos() const
{
	return (_currentPos);
}

const sf::Vector2f	&ObjectMover::getNextPos() const
{
	return (_nextPos);
}

void			ObjectMover::onMove(Position::dir direction)
{
	if (_entity.isMoveable() && !_moving)
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
		_nextPos += posOffset;
	}
}

void			ObjectMover::update()
{
	if (_previousPos != _nextPos && !_moving) // start move
	{
		_movement.restart();
		_moving = true;
	}
	else if (_previousPos != _nextPos && _moving) // move in progress
	{
		sf::Time	totalTime = _movement.getElapsedTime();

		if (totalTime.asSeconds() >= 0.25f) // move finish
		{
			_previousPos = _currentPos = _nextPos;
			_moving = false;
		}
		else // move in progress
		{
			float progress = totalTime.asSeconds() / 0.25f;

			_currentPos.x = _previousPos.x + (_nextPos.x - _previousPos.x) * progress;
			_currentPos.y = _previousPos.y + (_nextPos.y - _previousPos.y) * progress;
		}
	}
	// TODO !
}