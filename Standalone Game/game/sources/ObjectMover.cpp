#include "ObjectMover.hh"


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

sf::Vector2f	ObjectMover::getCurrentPos() const
{
	return (_currentPos);
}

void			ObjectMover::update()
{

	// TODO !
}