#ifndef BOSSALGO_H_
# define BOSSALGO_H_

#include	<vector>
#include	"types.hh"

class ABossAlgo
{
public:
	virtual ~ABossAlgo() {};
	virtual int	algo(std::vector<game::Pos> pos) = 0;
	std::vector<game::Pos>	&pos() { return _pos; }
	game::Type			&type() { return _type; }
	game::Pos			&firePos() { return _firePos; }
	int					&life() { return _life; }

protected:
	std::vector<game::Pos>	_pos;
	game::Pos			_firePos;
	game::Type			_type;
	int					_life;
};

#endif /* IAALGO_H_ */
