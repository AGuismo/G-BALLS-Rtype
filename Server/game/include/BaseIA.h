#pragma once

# include "IaAlgo.hh"

class BaseIA : public AIaAlgo
{
public:
	BaseIA();
	BaseIA(const BaseIA &src);
	~BaseIA();

	int	algo(IAPlayer &players);
	AIaAlgo *getInstance();

private:

};
