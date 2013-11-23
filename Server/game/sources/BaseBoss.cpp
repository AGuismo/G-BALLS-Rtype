#include "BaseBoss.h"

BaseBoss::BaseBoss(std::vector<game::Pos> &pos) : AIaAlgo()
{
	_pos = pos;
	_firePos = pos[pos.size() / 2];
//	_type = ;
	_life = 10;
}

BaseBoss::~BaseBoss()
{

}

int BaseBoss::algo(Game &game)
{
    (void)game;
	return -1;
}
