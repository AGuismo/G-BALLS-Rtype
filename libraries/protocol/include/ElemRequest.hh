#pragma once

#include	"Protocol.hpp"
#include	"AGameRequest.hh"
#include	"types.hh"

class Entity;

class ElemRequest : public AGameRequest
{
public:
  ElemRequest(requestCode::SessionID session = 0, game::Stamp stamp = 0);

  ~ElemRequest();

  ElemRequest(ElemRequest const&);
  ElemRequest& operator=(ElemRequest const&);

  template <class E>
  static const ElemRequest	create(const Entity &entity, requestCode::SessionID session,
				       game::Stamp stamp)
  {
    ElemRequest		created(session, stamp);

    created._entity = new E(entity);

    return (created);
  }

public:
  Protocol		&serialize(Protocol &) const;
  Protocol		&unserialize(Protocol &);
  ARequest		*clone() const;

public:
  game::Type		type() const;
  game::ID		ID() const;
  const Entity		*entity() const;

  template <class E>
  void			entity(const Entity &entity)
  {
    _entity = new E(entity);
  }

private:
  Entity		*_entity;
};
