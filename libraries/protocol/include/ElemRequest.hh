#pragma once

#include	"Protocol.hpp"
#include	"AGameRequest.hh"
#include	"ProtocolTypes.hh"

class	IEntityFactory;
class	Entity;

class ElemRequest : public AGameRequest
{
private:
  static const std::string	NO_ENTITY_FACTORY;

public:
  ElemRequest(const Entity &entity, rtype::protocol::SessionID session,
	      rtype::protocol::game::Stamp stamp);
  ElemRequest();

  ~ElemRequest();

  ElemRequest(ElemRequest const&);
  ElemRequest& operator=(ElemRequest const&);

public:
  Protocol		&serialize(Protocol &) const;
  Protocol		&unserialize(Protocol &);
  ARequest		*clone() const;

public:
  rtype::protocol::game::FullType	type() const;
  rtype::protocol::game::ID		ID() const;
  const Entity		*entity() const;
  void			entity(const Entity &entity);

private:
  Entity		*_entity;
  IEntityFactory	*_entityFactory;
};
