#include "ObjectMover.hh"


ObjectMover::ObjectMover(const Entity &entity, const Animation &anim):
_entity(entity), _animations(anim)
{
}

ObjectMover::ObjectMover()
{
}

ObjectMover::~ObjectMover()
{
}

ObjectMover::ObjectMover(const ObjectMover &src):
_entity(src._entity), _animations(src._animations)
{
}

ObjectMover	&ObjectMover::operator=(const ObjectMover &src)
{
	if (&src != this)
	{
		_entity = src._entity;
		_animations = src._animations;
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