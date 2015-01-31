#include	<iostream>
#include	"ElemRequest.hh"

#include	"Entity.hh"
#include	"Missile.hh"
#include	"Mob.hh"
#include	"Player.hh"

ElemRequest::ElemRequest(requestCode::SessionID session, game::Stamp stamp) :
  AGameRequest(requestCode::game::ELEM, session, stamp), _entity(0)
{
}

ElemRequest::ElemRequest(const ElemRequest &src) : AGameRequest(src), _entity(0)
{
  if (src._entity != 0)
    _entity = src._entity->copy();
}

ElemRequest	&ElemRequest::operator=(const ElemRequest &src)
{
  if (&src != this)
  {
    AGameRequest::operator=(src);
    if (src._entity != 0)
      _entity = src._entity->copy();
  }
  return (*this);
}

ElemRequest::~ElemRequest()
{
  delete _entity;
}

Protocol			&ElemRequest::serialize(Protocol &rhs) const
{
  rhs << _code << _sessionID << _stamp << *_entity;
  return rhs;
}

Protocol			&ElemRequest::unserialize(Protocol &rhs)
{
  Entity			e;

  rhs >> _sessionID >> _stamp >> e;
  switch (e.getType().desc.maj)
  {
  case Entity::MISSILE:
    _entity = new Missile(e);
    break;
  case Entity::PLAYER:
    _entity = new Player(e);
    break;
  case Entity::MOBS:
    _entity = new Mob(e);
    break;
  case Entity::BOSS:
    _entity = new Entity(e); // Not created yet
    break;
  case Entity::WALL:
    _entity = new Entity(e); // Not created yet
    break;
  case Entity::BONUS:
    _entity = new Entity(e); // Not created yet
    break;
  default:
    _entity = new Entity(e); // Not gonna happend theorically
    break;
  }
  return rhs;
}

ARequest			*ElemRequest::clone() const
{
  return (new ElemRequest(*this));
}

game::Type			ElemRequest::type() const
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
