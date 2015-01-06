#pragma once

#include	"Entity.hh"
#include	"Animation.hh"

class Referee;

class ObjectMover
{
public:
	static const float	DEFAULT_MOVEMENT_DURATION;

public:
	ObjectMover(const Entity &entity, const Animation &a, float movementDuration = 0.5f);
	ObjectMover();
	virtual ~ObjectMover();

	ObjectMover(const ObjectMover &src);
	ObjectMover		&operator=(const ObjectMover &src);

public:
	virtual void		update(Referee &);
	virtual void		onMove(Position::dir direction, Referee &);
	static Position	Vector2fToPosition(const sf::Vector2f &pos, Position::dir direction);

public:
	void				changeSpeed(short speed);
	void				forcePosition(const sf::Vector2f &currentPos);
	Animation			&getAnimation();
	const sf::Vector2f	&getPreviousPos() const;
	const sf::Vector2f	&getCurrentPos() const;
	const sf::Vector2f	&getNextPos() const;
	unsigned short		getObjectID() const;

protected:
	unsigned short	_objectID;
	short			_speed;
	Animation		_animations;

	struct
	{
		sf::Vector2f	previous;
		sf::Vector2f	current;
		sf::Vector2f	next;
	}					_position;

	struct
	{
		sf::Clock	timer;
		float		endTimer;
	}				_movement;

	float			_moveDuration;

	bool			_isMoving;

	bool			_isNextMoveAvailable;
	Position::dir	_nextMove;
};

