#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"

class BuffRequest : public AGameRequest
{
 public:
  BuffRequest();
  BuffRequest(Ruint16 id, Rint8 type);
  ~BuffRequest();

  BuffRequest(BuffRequest const&);
  BuffRequest& operator=(BuffRequest const&);

 public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();

 public:
  Ruint16				ID() const;
  void				ID(Ruint16 id);
  Rint8				type() const;
  void				type(Rint8 type);

 private:
  Ruint16				_id;
  Rint8				_type;
};

