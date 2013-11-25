#pragma once

# include "IaAlgo.hh"

class BaseIA : public AIaAlgo
{
public:
	BaseIA();
	~BaseIA();

	int	algo(IAPlayer &players);
	AIaAlgo *clone();
private:

};
