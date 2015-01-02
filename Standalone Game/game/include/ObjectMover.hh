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
	void			update();

public:
	Entity			&getEntity();
	Animation		&getAnimation();
	sf::Vector2f	getCurrentPos() const;

private:
	Entity			_entity;
	Animation		_animations;

	sf::Vector2f	_previousPos;
	sf::Vector2f	_currentPos;
	sf::Vector2f	_nextPos;
};

