#include "BaseIA.h"
#include <cstdlib>
#include <ctime>
#include "RequestCode.hh"
#include "Env.hh"

BaseIA::BaseIA()
{
	srand((unsigned int)(time(NULL)));
	_pos.push_back((15 * (rand() % rtype::Env::getInstance().game.mapSize + 1)) - 1);
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
