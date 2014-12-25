// -----------------------------------------------------------------------------
// STATEMANAGER
// -----------------------------------------------------------------------------
// Last update Thu Jun  6 11:19:08 2013 jules baratoux
// A kind of assosiative stack

#pragma once
#include <map>
#include <stack>
#include <string>
#include <iterator>

#include "Game.hpp"
#include "IState.hh"

namespace input
{
    class Manager;
}

namespace state
{
    class Manager
    {
	public:
	typedef std::map<const std::string, const IState *>	store_type;
	typedef std::map<const std::string, IState *>		inuse_type;
	typedef std::stack<inuse_type::iterator>		stack_type;


	Manager(input::Manager & inputManager);
	~Manager();


	void			add(const std::string & key, const IState * state);
	void			switchTo(const std::string & stateName);
	void			push(const std::string & stateName);
	void			pop(void);
	void			back(void);
	void			backTo(const std::string & stateName);

	inuse_type::iterator	end(void);
	inuse_type::iterator	find(const std::string & stateName);
	inuse_type::iterator	top(void);

	IState *		top(void) const;
	IState *		at(const std::string & stateName);

	void			update(void);
	void			draw(void);

	private:
	store_type		store;
	inuse_type		inuse;
	stack_type		stack;
	input::Manager &	inputManager;
    };
};
