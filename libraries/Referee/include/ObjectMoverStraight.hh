#pragma once

#include	"ObjectMover.hh"

class ObjectMoverStraight : public ObjectMover
{
public:
	ObjectMoverStraight(const Entity &e);
	ObjectMoverStraight();
	~ObjectMoverStraight();

	ObjectMoverStraight(const ObjectMoverStraight &src);
	ObjectMoverStraight	&operator=(const ObjectMoverStraight &src);

	bool			update();

private:
	Position::dir	_direction;
};