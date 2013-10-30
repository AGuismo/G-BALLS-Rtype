//
// Thread.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 12:27:48 2013 lambert kevin
// Last update Wed Oct 30 12:21:39 2013 lambert kevin
//

#ifndef		LINUXTHREAD_HH_
# define	LINUXTHREAD_HH_

# include	<pthread.h>
# include	"Bind.hpp"

template <typename T>
class Threads
{
  Function<T>		_func;
  pthread_t		_th;
  pthread_attr_t	_attr;
  bool			_detached;
  bool			_activated;

public:
  Threads(Function<T> func) :
    _func(func), _detached(false), _activated(false)
  {
    pthread_attr_init(&_attr);
  }

  virtual ~Threads()
  {
    if (_activated)
      pthread_cancel(_th);
  }

  bool		run()
  {
    if (_activated)
      return (false);
    if (pthread_create(&_th, &_attr, reinterpret_cast<void *(*)(void *)>(routine),
		       reinterpret_cast<void *>(this)) != 0)
      return (false);
    _activated = true;
    return (true);
  }

  bool		cancel()
  {
    if (_activated)
      if (pthread_cancel(_th) != 0)
	return (false);
    _activated = false;
    return (true);
  }

  template <typename U>
  bool		join(U *ret = 0)
  {
    if (_detached || !_activated)
      return (false);
    if (pthread_join(_th, reinterpret_cast<void **>(&ret)) != 0)
      return (false);
    _activated = false;
    return (true);
  }

  bool		join()
  {
    if (_detached || !_activated)
      return (false);
    if (pthread_join(_th, 0) != 0)
      return (false);
    _activated = false;
    return (true);
  }

  bool		setDetachState()
  {
    if (pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED) != 0)
      return (false);
    _detached = true;
    return (true);
  }

  bool		unsetDetachState()
  {
    if (pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_JOINABLE) != 0)
      return (false);
    _detached = false;
    return (true);
  }

  bool		getDetatchState() const
  {
    return (_detached);
  }
  bool		isActivated() const
  {
    return (_activated);
  }

private:
  static void	routine(Threads<T> *instance);
};

template <typename T>
void		Threads<T>::routine(Threads<T> *instance)
{
  instance->_func();
}

#endif /* LINUXTHREAD_HH_ */
