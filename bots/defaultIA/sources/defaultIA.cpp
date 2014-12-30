#include <cstdlib>
#include <ctime>
#include	"defaultIA.hh"
#include	"RequestCode.hh"
#include	<iostream>

DefaultIA::DefaultIA() : AIaAlgo()
{
	srand((unsigned int)(time(NULL)));
	_pos.push_back(15 * (rand() % 16));
 	_firePos = _pos[0];
	_life = 1;
	_type = requestCode::game::server::SBYDOS1;
	_isIa = true;
}

DefaultIA::~DefaultIA()
{

}

AIaAlgo *DefaultIA::clone()
{
    return new DefaultIA();
}

int	DefaultIA::algo(IAPlayer &players)
{
	(void)players;
	return 6;
}

extern "C"
{
	AIaAlgo *getInstance()
	{
		return new DefaultIA();
	}
}
