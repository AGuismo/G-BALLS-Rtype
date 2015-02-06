#include	"Entity.hh"
#include	"GameMap.hh"

using namespace rtype::protocol;

const char	*GameMap::ENTITY_ALREADY_EXIST_EXCEPT = "An entity with the same ID already exist.";
const char	*GameMap::ENTITY_DONT_EXIST_EXCEPT = "There is no entity with this ID on the map.";

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
  for (iterator it = begin(); it != end(); ++it)
    delete *it;
}

const GameMap::entity_set_type	&GameMap::getMap() const
{
  return (_entities);
}

GameMap::iterator	GameMap::begin()
{
  return (_entities.begin());
}

GameMap::const_iterator	GameMap::begin() const
{
  return (_entities.begin());
}

GameMap::iterator	GameMap::end()
{
  return (_entities.end());
}

GameMap::const_iterator	GameMap::end() const
{
  return (_entities.end());
}

Entity	*GameMap::findEntityByID(game::ID searchedEntityID) const
{
  Entity	searched;
  iterator	findMapIt;

  searched.setID(searchedEntityID);
  findMapIt = _entities.find(&searched);
  if (findMapIt == _entities.end())
    throw EntityDontExistException();
  return (*findMapIt);
}

void	GameMap::addEntity(const Entity &newEntity)
{
  if (entityExists(newEntity.getID()))
    throw EntityAlreadyExistException();
  _entities.insert(newEntity.copy());
}

void		GameMap::delEntity(rtype::protocol::game::ID deletedEntityID)
{
  Entity	toDelete;

  if (!entityExists(deletedEntityID))
    throw EntityDontExistException();
  toDelete.setID(deletedEntityID);
  _entities.erase(&toDelete);
}

bool	GameMap::entityExists(game::ID searchedEntityID)
{
  Entity	searched;

  searched.setID(searchedEntityID);
  return (_entities.find(&searched) != _entities.end());
}

// Comparison Function
bool	GameMap::KeyComparerFn::operator()(const Entity *lhs, const Entity *rhs) const
{
  return (lhs->getID() < rhs->getID());
}

// Exceptions
const char	*GameMap::EntityAlreadyExistException::what() const throw()
{
  return (ENTITY_ALREADY_EXIST_EXCEPT);
}

const char	*GameMap::EntityDontExistException::what() const throw()
{
  return (ENTITY_DONT_EXIST_EXCEPT);
}
