#pragma once

#include "IaAlgo.hh"
#include "Game.h"

class BaseBoss : public AIaAlgo
{
public:
	BaseBoss(std::vector<game::Pos> &pos);
	~BaseBoss();

	int algo(Game &game);

private:

};