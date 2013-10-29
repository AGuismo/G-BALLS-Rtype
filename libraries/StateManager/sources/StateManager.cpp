// -----------------------------------------------------------------------------
// STATEMANAGER
// -----------------------------------------------------------------------------
// Last update Fri Jun 14 18:59:06 2013 robin goupil

#include	"assert.hh"
#include	"StateManager.hh"
#include	"IState.hh"

using namespace state;

Manager::Manager(input::Manager & inputManager) : inputManager(inputManager) {}

Manager::~Manager(void) {}

IState *	Manager::top(void) const
{
    assert(stack.empty() == false);
    return stack.top()->second;
}

Manager::inuse_type::iterator	Manager::top(void)
{
    assert(stack.empty() == false);
    return stack.top();
}

Manager::inuse_type::iterator	Manager::end(void)
{
    return inuse.end();
}

Manager::inuse_type::iterator	Manager::find(const std::string & stateName)
{
    return inuse.find(stateName);
}

IState *	Manager::at(const std::string & stateName)
{
    assert(inuse.empty() == false);
    assert(inuse.find(stateName) != inuse.end());

    return inuse[stateName];
}

void		Manager::update(void)
{
    top()->second->update();
}

void		Manager::draw(void)
{
    top()->second->draw();
}

void		Manager::add(const std::string & key, const IState * state)
{
    assert(store.find(key) == store.end() && state != NULL);

    store[key] = state;
}

inline void		Manager::push(const std::string & stateName)
{
    assert(store.find(stateName) != store.end() );
    assert(inuse.find(stateName) == inuse.end() );

    IState *	clone = (*store[stateName]).clone();

    inuse[stateName] = clone;
    if (stack.size() > 0)
      top()->second->onEnd();
    stack.push(inuse.find(stateName));
    if (stack.size() > 0)
      top()->second->onStart();
}

void		Manager::switchTo(const std::string & stateName)
{
    push(stateName);
}

inline void		Manager::pop(void)
{
  if (stack.size() > 0)
    top()->second->onEnd();
  inuse.erase(top());
  stack.pop();
  if (stack.size() > 0)
    top()->second->onStart();
}

void		Manager::back(void)
{
    pop();
}

void		Manager::backTo(const std::string & stateName)
{
    assert(inuse.find(stateName) != inuse.end() );

    const inuse_type::iterator stateIt = inuse.find(stateName);

    while (stateIt != top() )
    {
	back();
    }
}
