#pragma once

#include	"ObjectMover.hh"

class ObjectMoverStraight : public ObjectMover
{
public:
	ObjectMoverStraight(const Entity &e, const Animation &a);
	ObjectMoverStraight();
	~ObjectMoverStraight();

	ObjectMoverStraight(const ObjectMoverStraight &src);
	ObjectMoverStraight	&operator=(const ObjectMoverStraight &src);

	void			update();
};