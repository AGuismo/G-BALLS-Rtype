#include	<iostream>
#include	"ElemRequest.hh"
#include	"Entity.hh"
#include	"IEntityFactory.hh"

using namespace rtype::protocol;

const std::string	ElemRequest::NO_ENTITY_FACTORY = "No EntityFactory Provided,\
 unserialize impossible.";

ElemRequest::ElemRequest(const Entity &entity, rtype::protocol::SessionID session, game::Stamp stamp) :
  AGameRequest(requestCode::game::ELEM, session, stamp), _entity(entity.copy()), _entityFactory(0)
{
}

ElemRequest::ElemRequest() :
  AGameRequest(requestCode::game::ELEM, 0, 0), _entity(0), _entityFactory(0)
{
}

ElemRequest::ElemRequest(const ElemRequest &src) : AGameRequest(src), _entity(0)
{
  if (src._entity != 0)
    _entity = src._entity->copy();
  _entityFactory = src._entityFactory;
}

ElemRequest	&ElemRequest::operator=(const ElemRequest &src)
{
  if (&src != this)
  {
    AGameRequest::operator=(src);
    if (src._entity != 0)
      _entity = src._entity->copy();
    _entityFactory = src._entityFactory;
  }
  return (*this);
}

ElemRequest::~ElemRequest()
{
  delete _entity;
}

Protocol			&ElemRequest::serialize(Protocol &rhs) const
{
  rhs << _code << _sessionID << _stamp;
  if (_entity != 0)
    rhs << *_entity;
  else
    rhs << entity::NONE;
  return rhs;
}

Protocol			&ElemRequest::unserialize(Protocol &rhs)
{
  game::FullType	entityType;

  rhs >> _sessionID >> _stamp >> entityType;
  if (_entityFactory == 0)
    throw Protocol::ConstructRequest(NO_ENTITY_FACTORY);
  _entity = _entityFactory->createEntityByType(entityType);
  rhs >> *_entity;
  // switch (e.getType().desc.maj)
  // {
  // case Entity::MISSILE:
  //   _entity = new Missile(e);
  //   break;
  // case Entity::PLAYER:
  //   _entity = new Player(e);
  //   break;
  // case Entity::MOBS:
  //   _entity = new Mob(e);
  //   break;
  // case Entity::BOSS:
  //   _entity = new Entity(e); // Not created yet
  //   break;
  // case Entity::WALL:
  //   _entity = new Entity(e); // Not created yet
  //   break;
  // case Entity::BONUS:
  //   _entity = new Entity(e); // Not created yet
  //   break;
  // default:
  //   _entity = new Entity(e); // Not gonna happend theorically
  //   break;
  // }
  return rhs;
}

ARequest			*ElemRequest::clone() const
{
  return (new ElemRequest(*this));
}

game::FullType			ElemRequest::type() const
{
  return _entity->getType().full;
}

game::ID			ElemRequest::ID() const
{
  return _entity->getID();
}

const Entity	*ElemRequest::entity() const
{
  return (_entity);
}

void	ElemRequest::entity(const Entity &entity)
{
  _entity = entity.copy();
}
