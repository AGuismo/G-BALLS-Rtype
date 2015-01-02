#pragma once

#include	"Entity.hh"
#include	"Animation.hh"

class ObjectMover
{
public:
	ObjectMover(const Entity &e, const Animation &a);
	ObjectMover();
	~ObjectMover();

	ObjectMover(const ObjectMover &src);
	ObjectMover		&operator=(const ObjectMover &src);

public:
	Entity		&getEntity();
	Animation	&getAnimation();

private:
	Entity		_entity;
	Animation	_animations;
};

