#include "BaseIa.h"

BaseIA::BaseIA(game::Pos pos)
{
	_pos.push_back(pos);
	_firePos = pos;
	_life = 1;
	_type = BASEIA;
}

BaseIA::~BaseIA()
{

}

int	BaseIA::algo(Game &game)
{
	return 6;
}