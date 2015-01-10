#include "NextStage.hh"

NextStageRequest::NextStageRequest(): AGameRequest(requestCode::game::NEXTSTAGE)
{}
NextStageRequest::~NextStageRequest()
{}

Protocol                        &NextStageRequest::serialize(Protocol &rhs) const
{
    rhs << _code << _sessionID << _stamp;
    return rhs;
}

Protocol                        &NextStageRequest::unserialize(Protocol &rhs)
{
    rhs >> _sessionID >> _stamp;
    return rhs;
}

ARequest                        *NextStageRequest::clone() const
{
    return new NextStageRequest();
}
