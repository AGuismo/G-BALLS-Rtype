#include "BaseIA.h"
#include <cstdlib>
#include <ctime>
#include "RequestCode.hh"

BaseIA::BaseIA()
{
	_pos.push_back((15 * (rand() % 15)));
	_firePos = _pos[0];
	_life = 1;
	_type = requestCode::game::server::SLIDER;
}

BaseIA::~BaseIA()
{

}

AIaAlgo	*BaseIA::clone()
{
    return new BaseIA();
}

int	BaseIA::algo(IAPlayer &players)
{
    (void)players;
    return 6;
}
