#include "BaseIA.h"
#include <cstdlib>
#include <ctime>
#include "RequestCode.hh"
#include "Env.hh"
#include <iostream>

BaseIA::BaseIA()
{
	_pos.push_back((rand() % 16 * 16) - 1);
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
