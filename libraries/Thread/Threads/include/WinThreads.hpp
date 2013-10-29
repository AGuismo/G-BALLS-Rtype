//
// Thread.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 12:27:48 2013 lambert kevin
// Last update Wed Oct 30 00:15:32 2013 lambert kevin
//

#ifndef		WINTHREAD_HPP_
# define	WINTHREAD_HPP_

# include	<Windows.h>
# include	<tchar.h>
# include	<strsafe.h>
# include	"Bind.hpp"

template <typename T, typename U>
class		Threads
{
  Function<T, U>	_func;
  HANDLE		_th;
  DWORD			_thid;
  bool			_detached;
  bool			_activated;

public:
  Threads(Function<T, U> func) :
    _func(func), _detached(false), _activated(false)
  {
  }

  Threads(T (*func)(U), U param) :
    _func(Func::Bind(func, param)), _detached(false), _activated(false)
  {
  }

   virtual ~Threads()
  {
	cancel();
  }

   bool		run()
  {
    if (_activated)
      return (false);
	if ((_th = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(routine),
							reinterpret_cast<LPVOID>(this), 0, &_thid)) == NULL)
      return (false);
    _activated = true;
    return (true);
  }

   bool		cancel()
  {
    if (_activated)
		if (!CloseHandle(_th))
			return (false);
    _activated = false;
	return (true);
  }

   bool		join(U *ret = 0)
  {
    if (_detached || !_activated)
      return (false);
	if (!WaitForSingleObject(_th, INFINITE))
      return (false);
    _activated = false;
    return (true);
  }

   bool		setDetachState()
  {
	return (false);
  }

   bool		unsetDetachState()
  {
	return (false);
  }

   bool		getDetatchState() const
  {
    return (false);
  }
   bool		isActivated() const
  {
    return (_activated);
  }

private:
  static void	routine(Threads<T, U> *instance);
};

template <typename T, typename U>
void		Threads<T, U>::routine(Threads<T, U> *instance)
{
  instance->_func();
}

#endif /* WINTHREAD_HPP_ */
