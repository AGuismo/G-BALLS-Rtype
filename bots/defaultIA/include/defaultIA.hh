#ifndef DEFAULTIA_H_
# define DEFAULTIA_H_

# include "IaAlgo.hh"

class BaseIA : public AIaAlgo
{
public:
	BaseIA(game::Pos pos);
	~BaseIA();

	int	algo(IAPlayer &players);

private:

};


#endif /* DEFAULTIA_H_ */
