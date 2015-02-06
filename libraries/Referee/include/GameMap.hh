#ifndef GAMEMAP_H_
# define GAMEMAP_H_

# include	<set>
# include	"ProtocolTypes.hh"

class	Entity;

class	GameMap
{
public:
  class	KeyComparerFn
  {
  public:
    bool	operator()(const Entity *lhs, const Entity *rhs) const;
  };

public:
  typedef std::set<Entity *, KeyComparerFn>	entity_set_type;
  typedef entity_set_type::iterator		iterator;
  typedef entity_set_type::const_iterator	const_iterator;

public:
  static const char	*ENTITY_ALREADY_EXIST_EXCEPT;
  static const char	*ENTITY_DONT_EXIST_EXCEPT;

  class	EntityAlreadyExistException : public std::exception
  {
    const char	*what() const throw();
  };

  class	EntityDontExistException : public std::exception
  {
    const char	*what() const throw();
  };


public:
  GameMap();
  virtual ~GameMap();

  Entity		*findEntityByID(rtype::protocol::game::ID entityID) const;
  const entity_set_type	&getMap() const;

  void			addEntity(const Entity &newEntity);
  void			delEntity(rtype::protocol::game::ID deletedEntity);
  bool			entityExists(rtype::protocol::game::ID searchedEntityID);

  iterator		begin();
  const_iterator	begin() const;
  iterator		end();
  const_iterator	end() const;

public:
  GameMap(GameMap const&);
  GameMap& operator=(GameMap const&);


private:
  entity_set_type	_entities;
};

#endif /* GAMEMAP_H_ */
