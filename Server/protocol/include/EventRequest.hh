#pragma once

#include	"AGameRequest.hh"
#include	"Protocol.hpp"

class EventRequest : public AGameRequest
{
public:
  EventRequest(Ruint8 event, Ruint8 param);
  ~EventRequest();

  EventRequest(EventRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();
  Ruint8				event()const;
  void				event(const Ruint8 &);
  Ruint8				param()const;
  void				param(const Ruint8 &);
private:
  Ruint8	_event;
  Ruint8	_param;
};
