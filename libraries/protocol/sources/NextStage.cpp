#include "NextStage.hh"

NextStageRequest::NextStageRequest(): AGameRequest(requestCode::game::NEXTSTAGE)
{}
NextStageRequest::~NextStageRequest()
{}

Protocol                        &NextStageRequest::serialize(Protocol &rhs) const
{
    rhs << _code << _sessionID;
    return rhs;
}

Protocol                        &NextStageRequest::unserialize(Protocol &rhs)
{
    rhs >> _sessionID;
    return rhs;
}

ARequest                        *NextStageRequest::clone()
{
    return new NextStageRequest();
}
