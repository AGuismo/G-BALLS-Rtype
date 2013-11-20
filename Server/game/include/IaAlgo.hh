//
// IaAlgo.hh for IaAlgo in /home/gherab_f/git/G-BALLS-Rtype/Server/game
//
// Made by francois gherabi
// Login   <gherab_f@epitech.net>
//
// Started on  Tue Nov 19 19:49:26 2013 francois gherabi
// Last update Tue Nov 19 20:27:01 2013 francois gherabi
//

#include	"Game.h"
#include	"types.hh"

#ifndef IAALGO_H_
# define IAALGO_H_

class AIaAlgo
{
    public:
    virtual ~AIaAlgo() {};
    virtual int	algo(Game &game) = 0;
    virtual std::vector<game::Pos>	&pos() = 0;
    virtual game::Type			&type() = 0;

    private:
    std::vector<game::Pos>	_pos;
    game::Type			_type;
};

#endif /* IAALGO_H_ */
