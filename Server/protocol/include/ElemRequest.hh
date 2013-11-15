#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"

class ElemRequest : public AGameRequest
{
public:
  ElemRequest();
  ElemRequest(Rint8 type, Rint32 pos, Rint8 dir, Ruint16 id);
  ~ElemRequest();

  ElemRequest(ElemRequest const&);
  ElemRequest& operator=(ElemRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();

public:
  Rint8			type() const;
  void			type(Rint8 t);
  Rint32		pos() const;
  void			pos(Rint32 p);
  Rint8			dir() const;
  void			dir(Rint8 d);
  Ruint16		ID() const;
  void			ID(Ruint16 id);

private:
  Rint8			_type;
  Rint32		_pos;
  Rint8			_dir;
  Ruint16		_id;
};
