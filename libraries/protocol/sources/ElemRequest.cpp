#include	<iostream>
#include	"ElemRequest.hh"

#include	"Entity.hh"
#include	"Missile.hh"
#include	"Mob.hh"
#include	"Player.hh"

ElemRequest::ElemRequest() : AGameRequest(requestCode::game::ELEM)
{
}

ElemRequest::ElemRequest(const ElemRequest &src) : AGameRequest(src)
{
	_entity = src._entity->copy();
}

ElemRequest::~ElemRequest()
{
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
	rhs >> *_entity;
	return rhs;
}

ARequest			*ElemRequest::clone() const
{
	return (new ElemRequest());
}

game::Type			ElemRequest::type() const
{
	return _entity->getType().full;
}

void			ElemRequest::type(game::Type t)
{
	_entity->setType(Entity::createType(t));
}

game::ID			ElemRequest::ID() const
{
	return _entity->getID();
}

void			ElemRequest::ID(game::ID id)
{
	_entity->setID(id);
}

const Entity	*ElemRequest::entity() const
{
	return (_entity);
}