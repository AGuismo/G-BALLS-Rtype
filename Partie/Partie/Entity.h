#pragma once

#include <map>

class Refere;
class Partie;
class Missile;

enum DIR
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};

enum TYPE
{
	WALL,
	DESTRUCTIBLEWALL,
	MISSILE,
	IA,
	BOSS,
	PLAYER
};

class Entity
{
public:
	Entity(TYPE type, int x, int y, int life, DIR dir, int length, int height);
	~Entity();
	virtual	void	update();

protected:
	int				_id;
	int				_life;
	DIR				_dir;
	unsigned int	_speed;
	int				_posx;
	int				_posy;
	TYPE			_type;
	int				_length;
	int				_height;

	friend Refere;
	friend Partie;
	/*
public:
	int				getId() const { return _id;};
	int				getLife() const { return _life;};
	DIR				getDir() const { return _dir;};
	int				getSpeed() const { return _speed;};
	int				getX() const { return _posx;};
	int				getY() const { return _posy;};
	TYPE			getType() const { return _type;};
	*/

};