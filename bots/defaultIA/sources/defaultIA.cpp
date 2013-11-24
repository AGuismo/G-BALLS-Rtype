#include <cstdlib>
#include <ctime>
#include	"defaultIA.hh"

DefaultIA::DefaultIA()
{
	srand((unsigned int)(time(NULL)));
	_pos.push_back(15 * (rand() % 16));
	_firePos = _pos[0];
	_life = 1;
	_type = BASEIA;
}

DefaultIA::DefaultIA(const DefaultIA &src)
{
	static_cast<void>(src);
	srand((unsigned int)(time(NULL)));
	_pos.push_back(15 * (rand() % 16));
	_firePos = _pos[0];
	_life = 1;
	_type = BASEIA;
}

DefaultIA::~DefaultIA()
{

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
