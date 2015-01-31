#pragma once

#include "Protocol.hpp"
#include "AGameRequest.hh"

class ScoreRequest : public AGameRequest
{
public:
  ScoreRequest();
  ScoreRequest(Ruint16 id, Ruint16 score);
  ~ScoreRequest();

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone() const;

public:
  Ruint16				ID() const;
  void				ID(Ruint16 id);
  Ruint16				score() const;
  void				score(Ruint16 score);

private:
  Ruint16				_id;
  Ruint16				_score;
};
