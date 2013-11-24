#pragma once

#include <vector>
#include "IaAlgo.hh"

class BaseBoss : public AIaAlgo
{
public:
	BaseBoss();
	BaseBoss(const BaseBoss &src);
	~BaseBoss();

	int algo(IAPlayer &players);
	AIaAlgo *getInstance();
	AIaAlgo *clone();
private:

};
