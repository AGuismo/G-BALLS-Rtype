// -----------------------------------------------------------------------------
// ISTATE
// -----------------------------------------------------------------------------
// Last update Fri Jun 14 18:35:30 2013 robin goupil

#pragma once
#include "Game.hpp"

namespace	state
{
    class		IState
    {
	public:
	virtual ~IState(void) {}

      virtual void	onStart(void) = 0;
	virtual IState*	clone(void) const = 0;
	virtual void	update(void) = 0;
	virtual void	draw(void) = 0;
      virtual void	onEnd(void) = 0;
    };
};
