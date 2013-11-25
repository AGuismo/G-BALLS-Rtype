#pragma once

#include <vector>
#include "IaAlgo.hh"

class IAALGO_API DefaultBoss : public AIaAlgo
{
public:
	DefaultBoss();
	~DefaultBoss();

	int algo(IAPlayer &players);
	AIaAlgo	*clone();
private:

};
