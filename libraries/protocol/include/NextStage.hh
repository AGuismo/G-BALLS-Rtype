#pragma once

#include        "AGameRequest.hh"
#include        "Protocol.hpp"

class NextStageRequest : public AGameRequest
{
    public:
    NextStageRequest();
    ~NextStageRequest();

    public:
    Protocol                      &serialize(Protocol &) const;
    Protocol                      &unserialize(Protocol &);
    ARequest                      *clone();
    private:
};
