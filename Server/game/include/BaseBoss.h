#pragma once

#include <vector>
#include "IaAlgo.hh"

class BaseBoss : public AIaAlgo
{
public:
	BaseBoss(std::vector<game::Pos> &pos);
	~BaseBoss();

	int algo(IAPlayer &players);

private:

};