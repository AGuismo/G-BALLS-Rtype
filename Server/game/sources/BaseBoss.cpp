#include "BaseBoss.h"
#include <cstdlib>
#include "RequestCode.hh"

BaseBoss::BaseBoss() : AIaAlgo()
{
	_pos.push_back(15 * (rand() % 13));
	_pos.push_back(_pos.back() + 30);
	_pos.push_back(_pos.back() + 30);
	_firePos = _pos[_pos.size() / 2];
	_type = requestCode::game::server::SHRIMP_BOSS;
	_life = 10;
	_isIa = false;
}

BaseBoss::BaseBoss(const BaseBoss &src)
{
	static_cast<void>(src);
	_pos.push_back(15 * (rand() % 13));
	_pos.push_back(_pos.back() + 30);
	_pos.push_back(_pos.back() + 30);
	_firePos = _pos[_pos.size() / 2];
	_type = requestCode::game::server::SHRIMP_BOSS;
	_life = 10;
	_isIa = false;
}

BaseBoss::~BaseBoss()
{

}

AIaAlgo *BaseBoss::getInstance()
{
	return new BaseBoss(*this);
}

AIaAlgo	*BaseBoss::clone()
{
    return new BaseBoss(*this);
}

int BaseBoss::algo(IAPlayer &players)
{
    (void)players;
	return 6;
}
