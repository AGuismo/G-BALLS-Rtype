#ifndef DEFAULTIA_H_
# define DEFAULTIA_H_

# include "IaAlgo.hh"

class DefaultIA : public AIaAlgo
{
public:
	DefaultIA();
	DefaultIA(const DefaultIA &src);
	~DefaultIA();

	int	algo(IAPlayer &players);
	AIaAlgo *getInstance();
private:

};


#endif /* DEFAULTIA_H_ */