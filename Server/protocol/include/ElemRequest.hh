#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"
#include "types.hh"

class ElemRequest : public AGameRequest
{
public:
  ElemRequest();
  ElemRequest(game::Type type, game::Pos pos, game::Dir dir, game::ID id);
  ~ElemRequest();

  ElemRequest(ElemRequest const&);
  ElemRequest& operator=(ElemRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();

public:
  game::Type		type() const;
  void			type(game::Type t);
  game::Pos		pos() const;
  void			pos(game::Pos p);
  game::Dir		dir() const;
  void			dir(game::Dir d);
  game::ID		ID() const;
  void			ID(game::ID id);

private:
  game::Type		_type;
  game::Pos		_pos;
  game::Dir		_dir;
  game::ID		_id;
};
