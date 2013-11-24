#include "BaseIA.h"
#include <cstdlib>

BaseIA::BaseIA()
{
	_pos.push_back((15 * rand() % 16));
	_firePos = _pos[0];
	_life = 1;
	_type = BASEIA;
}

BaseIA::BaseIA(const BaseIA &src)
{
	static_cast<void>(src);
	_pos.push_back((15 * rand() % 16));
	_firePos = _pos[0];
	_life = 1;
	_type = BASEIA;
}

BaseIA::~BaseIA()
{

}

AIaAlgo *BaseIA::getInstance()
{
	return new BaseIA(*this);
}

int	BaseIA::algo(IAPlayer &players)
{
    (void)players;
    return 6;
}
