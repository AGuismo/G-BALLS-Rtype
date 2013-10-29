//
// MenuState.hh for  in /home/lamber_k/Dropbox/Projects/module_4e_sem/StateManager
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Thu May 16 14:07:14 2013 lambert kevin
// Last update Thu May 23 14:48:44 2013 lambert kevin
//

#ifndef MENUSTATE_HH_
# define MENUSTATE_HH_

# include	"IState.hh"
# include	"Game.hpp"

class MenuState : public state::IState
{
public:
  MenuState(void);
  virtual ~MenuState(void);

public:
  void		draw(void);
  void		update(gdl::GameClock const &, gdl::Input &);
  void		update(void);
};

#endif /* MENUSTATE_HH_ */
