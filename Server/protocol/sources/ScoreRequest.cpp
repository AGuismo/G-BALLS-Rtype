#include "ScoreRequest.h"

ScoreRequest::ScoreRequest() : AGameRequest(requestCode::game::SCORE)
{

}

ScoreRequest::ScoreRequest(Ruint16 id, Ruint16 score) :
AGameRequest(requestCode::game::SCORE), _id(id), _score(score)
{

}

Protocol			&ScoreRequest::serialize(Protocol &rhs) const
{
	rhs << _id;
	rhs << _score;
	return rhs;
}

Protocol		&ScoreRequest::unserialize(Protocol &rhs)
{
	rhs >> _id;
	rhs >> _score;
	return rhs;
}

ARequest		*ScoreRequest::clone()
{
	return new ScoreRequest(_id, _score);
}

Ruint16			ScoreRequest::ID() const
{
	return _id;
}

void			ScoreRequest::ID(Ruint16 id)
{
	_id = id;
}

Ruint16				ScoreRequest::score() const
{
	return _score;
}

void				ScoreRequest::score(Ruint16 score)
{
	_score = score;
}