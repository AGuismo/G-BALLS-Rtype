#include "DefaultBoss.h"

DefaultBoss::DefaultBoss() : AIaAlgo()
{
	_pos.push_back(15 * (rand() % 13));
	_pos.push_back(_pos.back() + 30);
	_pos.push_back(_pos.back() + 30);
	_firePos = _pos[_pos.size() / 2];
//	_type = ;
	_life = 10;
	_isIa = false;
}

DefaultBoss::DefaultBoss(const DefaultBoss &src) : AIaAlgo()
{
	static_cast<void>(src);
	_pos.push_back(15 * (rand() % 13));
	_pos.push_back(_pos.back() + 30);
	_pos.push_back(_pos.back() + 30);
	_firePos = _pos[_pos.size() / 2];
	//	_type = ;
	_life = 10;
	_isIa = false;
}

DefaultBoss::~DefaultBoss()
{

}

AIaAlgo *DefaultBoss::getInstance()
{
	return new DefaultBoss(*this);
}

int DefaultBoss::algo(IAPlayer &players)
{
    (void)players;
	_fires.push_back(6);
	return -1;
}
