#include	<cstdlib>
#include	"DefaultBoss.h"
#include	"RequestCode.hh"

DefaultBoss::DefaultBoss() : AIaAlgo()
{
	_pos.push_back(15 * (rand() % 13));
	_pos.push_back(_pos.back() + 30);
	_pos.push_back(_pos.back() + 30);
	_firePos = _pos[_pos.size() / 2];
	_life = 10;
	_isIa = false;
	_type = requestCode::game::server::SHRIMP_BOSS;
}

DefaultBoss::~DefaultBoss()
{

}

AIaAlgo	*DefaultBoss::clone()
{
    return new DefaultBoss();
}


int DefaultBoss::algo(IAPlayer &players)
{
    (void)players;
	return 6;
}
extern "C"
{
	AIaAlgo *getInstance()
	{
		return new DefaultBoss();
	}
}
