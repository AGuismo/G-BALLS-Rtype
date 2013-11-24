#pragma once

#include <vector>
#include "IaAlgo.hh"

class DefaultBoss : public AIaAlgo
{
public:
	DefaultBoss();
	DefaultBoss(const DefaultBoss &src);
	~DefaultBoss();

	int algo(IAPlayer &players);
	AIaAlgo *getInstance();
private:

};