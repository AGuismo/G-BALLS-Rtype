#pragma once

#include <vector>
#include "IaAlgo.hh"

class DefaultBoss : public AIaAlgo
{
public:
	DefaultBoss(std::vector<game::Pos> &pos);
	~DefaultBoss();

	int algo(IAPlayer &players);

private:

};