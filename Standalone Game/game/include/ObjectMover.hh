#pragma once

#include	"Entity.hh"
#include	"Animation.hh"

class ObjectMover
{
public:
	ObjectMover(const Entity &e, const Animation &a);
	ObjectMover();
	virtual ~ObjectMover();

	ObjectMover(const ObjectMover &src);
	ObjectMover		&operator=(const ObjectMover &src);

public:
	void			update();

public:
	Entity				&getEntity();
	Animation			&getAnimation();
	const sf::Vector2f	&getPreviousPos() const;
	const sf::Vector2f	&getCurrentPos() const;
	const sf::Vector2f	&getNextPos() const;
	void				onMove(Position::dir direction);

private:
	Entity			_entity;
	Animation		_animations;

	sf::Vector2f	_previousPos;
	sf::Vector2f	_currentPos;
	sf::Vector2f	_nextPos;
	sf::Clock		_movement;
	bool			_moving;
};

