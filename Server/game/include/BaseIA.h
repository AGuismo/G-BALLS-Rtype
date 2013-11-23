#pragma once

# include "IaAlgo.hh"

class BaseIA : public AIaAlgo
{
public:
	BaseIA(game::Pos pos);
	~BaseIA();

	int	algo(Game &game);

private:

};
