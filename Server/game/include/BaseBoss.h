#pragma once

#include <vector>
#include "IaAlgo.hh"

class BaseBoss : public AIaAlgo
{
public:
	BaseBoss();
	~BaseBoss();

	int algo(IAPlayer &players);
	AIaAlgo *clone();
private:

};
