//
// IaAlgo.hh for IaAlgo in /home/gherab_f/git/G-BALLS-Rtype/Server/game
//
// Made by francois gherabi
// Login   <gherab_f@epitech.net>
//
// Started on  Tue Nov 19 19:49:26 2013 francois gherabi
// Last update Tue Nov 19 20:27:01 2013 francois gherabi
//

#ifndef IAALGO_H_
# define IAALGO_H_

#include	<list>
#include	<vector>
#include	"types.hh"
#include	"IAPlayer.hpp"

class AIaAlgo
{
public:
	static const game::Type BASEIA = 8;

public:
    virtual ~AIaAlgo() {};
	virtual int	algo(IAPlayer &players) = 0;
	virtual AIaAlgo *getInstance() = 0;
	std::vector<game::Pos>	&pos() { return _pos; }
	std::list<game::Dir>	&fires() { return _fires; }
	game::Type			&type() { return _type; }
	game::Pos			&firePos() { return _firePos; }
	int					&life() { return _life; }
	virtual bool isIa() { return _isIa; }

    protected:
    std::vector<game::Pos>	_pos;
	std::list<game::Dir>	_fires;
	game::Pos			_firePos;
    game::Type			_type;
	int					_life;
	bool				_isIa;
};

#endif /* IAALGO_H_ */
