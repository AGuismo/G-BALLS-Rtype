#include "BaseIA.h"
#include <cstdlib>
#include "RequestCode.hh"

BaseIA::BaseIA()
{
	_pos.push_back((15 * (rand() % 16)));
	_firePos = _pos[0];
	_life = 1;
	_type = requestCode::game::server::SBYDOS1;
}

BaseIA::BaseIA(const BaseIA &src)
{
	static_cast<void>(src);
	_pos.push_back((15 * (rand() % 16)));
	_firePos = _pos[0];
	_life = 1;
	_type = requestCode::game::server::SBYDOS1;
}

BaseIA::~BaseIA()
{

}

AIaAlgo *BaseIA::getInstance()
{
	return new BaseIA(*this);
}

AIaAlgo	*BaseIA::clone()
{
    return new BaseIA(*this);
}

int	BaseIA::algo(IAPlayer &players)
{
    (void)players;
    return 6;
}
