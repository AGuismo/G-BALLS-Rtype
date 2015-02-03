#pragma once

#include	"Position.hh"

class Protocol;

class Entity
{
public:
  enum majortype : unsigned char
  {
    NONE,
      PLAYER,
      BOSS,
      MOBS,
      WALL,
      BONUS,
      MISSILE
      };

  typedef unsigned char	minortype;
  typedef short		velocity;

  union	type
  {
    struct
    {
      majortype		maj;
      minortype		min;
    }			desc;
    unsigned short	full;
  };

public:
  Entity(type t, unsigned short id, const Position &pos,
	 velocity v, short hp, short shield,
	 unsigned short height, unsigned short width);
  Entity();
  virtual ~Entity();

public:
  Entity(const Entity &src);
  Entity		&operator=(const Entity &src);

public:
  static type		createType(majortype maj, minortype min = 0);
  static type		createType(unsigned short full);

public:
  bool			isMoveable() const;
  velocity		speed() const;
  void			speed(velocity v);

public:
  bool			isDestructible() const;
  short			hp() const;
  void			hp(short hp);
  short			shield() const;
  void			shield(short shield);

public:
  type			getType() const;
  void			setType(const type &t);
  unsigned short	getID() const;
  void			setID(unsigned short ID);
  Position		getPosition() const;
  void			setPosition(const Position &pos);
  unsigned short	getHeight() const;
  void			setHeight(unsigned short Height);
  unsigned short	getWidth() const;
  void			setWidth(unsigned short Width);

public:
  friend Protocol	&operator<<(Protocol &protocol, const Entity &e)
  {
    e.serialize(protocol);
    return (protocol);
  }

  friend Protocol	&operator>>(Protocol &protocol, Entity &e)
  {
    e.unserialize(protocol);
    return (protocol);
  }

  virtual void		serialize(Protocol &) const;
  virtual void		unserialize(Protocol &);
  virtual Entity	*copy() const;

protected:
  type			_type;
  unsigned short	_id;
  Position		_p;
  unsigned short	_height;
  unsigned short	_width;

  bool			_isMoveable;
  velocity		_velocity;

  bool			_isDestructible;
  short			_hp;
  short			_shield;
};

struct EntityComparer : public Entity
{
  EntityComparer() {};
  EntityComparer(unsigned int id)
  {
    _id = id;
  }
  ~EntityComparer() {};

  void	id(unsigned int id)
  {
    _id = id;
  }
};