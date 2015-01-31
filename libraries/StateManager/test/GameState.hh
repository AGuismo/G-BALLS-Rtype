//
// GameState.hh for  in /home/lamber_k/Dropbox/Projects/module_4e_sem/StateManager
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Thu May 16 14:07:29 2013 lambert kevin
// Last update Thu May 23 14:48:44 2013 lambert kevin
//

#ifndef GAMESTATE_HH_
# define GAMESTATE_HH_

# include	"IState.hh"
# include	"Game.hpp"

class GameState : public state::IState
{
    int i;
public:
  GameState(void);
  virtual ~GameState(void);

public:
    void		draw(void);
    void		update(gdl::GameClock const &, gdl::Input &);
    void		update(void);
};

#endif /* GAMESTATE_HH_ */
