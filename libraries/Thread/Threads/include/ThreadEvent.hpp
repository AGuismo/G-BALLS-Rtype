#ifndef EVENT_H_
# define EVENT_H_

#include	<deque>
#include	"ThreadMutex.hh"
#include	"ThreadCond.hh"

struct		timespec;

namespace	Thread
{
  template <typename T>
  class EventQueue
  {
    typedef typename std::deque<T *>::iterator EventIt;

  private:
  public:
    std::deque<T *>	_stack;
    Thread::Mutex	_m;
    Thread::Cond	_condNotEmpty;
    Thread::Cond	_condNotFull;
    // Thread::Cond	_condEmpty;
    int			_maxPendingEvents;
    bool		_blocking;

  public:
    EventQueue(int maxPendingEvents = 0, bool blocking = true) :
      _maxPendingEvents(maxPendingEvents), _blocking(blocking)
    {

    }

    ~EventQueue()
    {
      for (EventIt it = _stack.begin(); it != _stack.end(); ++it)
	delete *it;
    }

  public:
    T		*pop()
    {
      Thread::MutexGuard	guard(_m);

      if (empty() && !_blocking)
	return (NULL);
      while (empty())
	_condNotEmpty.wait(_m);
      if (_maxPendingEvents != 0 &&
	  _stack.size() == _maxPendingEvents)
      	_condNotFull.broadcast();
      // if (_stack.size() == 0)
      // 	_condEmpty.signal();
      return (getData());
    }

    bool		push(T *data, Thread::Cond::msTime mstime = 0)
    {
      Thread::MutexGuard	guard(_m);

      if (!_blocking && _maxPendingEvents != 0 && _stack.size() == _maxPendingEvents)
	return (false);
      while (_maxPendingEvents != 0 && _stack.size() == _maxPendingEvents)
	_condNotFull.wait(_m);
      _condNotEmpty.broadcast();
      _stack.push_back(data);
      return (true);
    }

    bool		empty() const
    {
      return (_stack.empty());
    }

  private:
    T		*getData()
    {
      T	*data = _stack.front();

      _stack.pop_front();
      return (data);
    }

  private:
    EventQueue(EventQueue const&);
    EventQueue& operator=(EventQueue const&);
  };
}

#endif /* EVENT_H_ */
