#pragma once

#include	"Entity.hh"
#include	"Clock.hh"

class ObjectMover
{
public:
	static const float	DEFAULT_MOVEMENT_DURATION;

public:
	ObjectMover(const Entity &entity, float movementDuration = 0.5f);
	ObjectMover();
	virtual ~ObjectMover();

	ObjectMover(const ObjectMover &src);
	ObjectMover		&operator=(const ObjectMover &src);

public:
	virtual bool		update();
	virtual void		onMove(Position::dir direction);

public:
	void				changeSpeed(short speed);
	void				forcePosition(const Position &currentPos);
	const Position		&getPreviousPos() const;
	const Position		&getCurrentPos() const;
	const Position		&getNextPos() const;
	unsigned short		getObjectID() const;
	unsigned int		getLastUpdate() const;
	void				setLastUpdate(unsigned int stamp);

protected:
	unsigned short	_objectID;
	short			_speed;

	struct
	{
		Position		previous;
		Position		current;
		Position		next;
	}					_position;

	struct
	{
		Clock		timer;
		float		endTimer;
	}				_movement;

	float			_moveDuration;

	bool			_isMoving;

	bool			_isNextMoveAvailable;
	Position::dir	_nextMove;
	unsigned int		_lastUpdate;
};

struct ObjectMoverComparer : public ObjectMover
{
	ObjectMoverComparer() {};
	ObjectMoverComparer(unsigned int id)
	{
		_objectID = id;
	}
	~ObjectMoverComparer() {};

	void	id(unsigned int id)
	{
		_objectID = id;
	}

};
