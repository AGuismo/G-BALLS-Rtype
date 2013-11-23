#include "DefaultBoss.h"

DefaultBoss::DefaultBoss(std::vector<game::Pos> &pos) : AIaAlgo()
{
	_pos = pos;
	_firePos = pos[pos.size() / 2];
//	_type = ;
	_life = 10;
}

DefaultBoss::~DefaultBoss()
{

}

int DefaultBoss::algo(IAPlayer &players)
{
    (void)players;
	_fires.push_back(6);
	return -1;
}
