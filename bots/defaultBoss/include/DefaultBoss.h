#pragma once

#include <vector>
#include "IaAlgo.hh"

class IAALGO_API DefaultBoss : public AIaAlgo
{
public:
	DefaultBoss();
	DefaultBoss(const DefaultBoss &src);
	~DefaultBoss();

	int algo(IAPlayer &players);
private:

};
