#pragma once

#include	"Protocol.hpp"
#include	"AGameRequest.hh"
#include	"types.hh"

class Entity;

class ElemRequest : public AGameRequest
{
public:
  ElemRequest();
  template <class E>
  ElemRequest(const E &entity, requestCode::SessionID session, game::Stamp stamp) : 
	  AGameRequest(requestCode::game::ELEM, session, stamp)
  {
	  _entity = new E(entity);
  }
  ~ElemRequest();

  ElemRequest(ElemRequest const&);
  ElemRequest& operator=(ElemRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone() const;

public:
  game::Type		type() const;
  void			type(game::Type t);
  game::ID		ID() const;
  void			ID(game::ID id);

  const Entity	*entity() const;

  template <class E>
  void			entity(const E entity)
  {
	  _entity = new E(entity);
  }

private:
	Entity		*_entity;
};
