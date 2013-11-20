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
    typedef typename std::deque<T>		event_stack;
    typedef typename std::deque<T>::iterator	EventIt;

  private:
  public:
    event_stack		_stack;
    Thread::Mutex	_m;
    Thread::Cond	_condNotEmpty;
    Thread::Cond	_condNotFull;
    Thread::Cond	_condEmpty;
    typename event_stack::size_type	_maxPendingEvents;

  public:
    EventQueue(int maxPendingEvents = 0) :
      _maxPendingEvents(maxPendingEvents)
    {

    }

    ~EventQueue()
    {
      for (EventIt it = _stack.begin(); it != _stack.end(); ++it)
	delete *it;
    }

  public:
    T		pop(bool blocking = true)
    {
      Thread::MutexGuard	guard(_m);

      if (empty() && !blocking)
	return (NULL);
      while (empty())
	_condNotEmpty.wait(_m);
      if (_maxPendingEvents != 0 &&
	  _stack.size() == _maxPendingEvents)
      	_condNotFull.broadcast();
      return (getData());
    }

    bool		push(T data, bool blocking = true)
    {
      Thread::MutexGuard	guard(_m);

      if (!blocking && _maxPendingEvents != 0 && _stack.size() == _maxPendingEvents)
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
    T		getData()
    {
      T		data = _stack.front();

      _stack.pop_front();
      return (data);
    }

    std::vector<T>	flushData()
    {
      std::vector<T>	output;

      while (!empty())
	output = getData();
      return (output);
    }

  private:
    EventQueue<T>(EventQueue<T> const&);
    EventQueue<T>& operator=(EventQueue<T> const&);
  };
}

#endif /* EVENT_H_ */
