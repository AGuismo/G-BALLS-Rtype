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

DefaultIA::DefaultIA(const DefaultIA &src)
{
	static_cast<void>(src);
	srand((unsigned int)(time(NULL)));
	_pos.push_back(15 * (rand() % 16));
	for (int i = 0; i != 50; i++)
		std::cout << _pos[0] << std::endl;
	_firePos = _pos[0];
	_life = 1;
	_type = requestCode::game::server::SBYDOS1;
}

DefaultIA::~DefaultIA()
{

}

AIaAlgo *DefaultIA::clone()
{
    return new DefaultIA(*this);
}

extern "C"
{
	AIaAlgo *getInstance()
	{
		return new DefaultIA();
	}
}

int	DefaultIA::algo(IAPlayer &players)
{
	(void)players;
	return 6;
}
