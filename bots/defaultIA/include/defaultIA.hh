#ifndef DEFAULTIA_H_
# define DEFAULTIA_H_

# include "IaAlgo.hh"

class IAALGO_API DefaultIA : public AIaAlgo
{
public:
	DefaultIA();
	~DefaultIA();

	virtual int	algo(IAPlayer &players);
	virtual AIaAlgo	*clone();
private:

};

#endif /* DEFAULTIA_H_ */
