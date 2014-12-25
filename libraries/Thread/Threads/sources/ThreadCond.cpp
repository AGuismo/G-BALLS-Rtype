//
// ThreadCond.cpp for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/sources
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 14:22:56 2013 lambert kevin
// Last update Fri Oct 25 05:50:48 2013 lambert kevin
//

#include	<iostream>
#include	"ThreadCond.hh"
#include	"ThreadMutex.hh"

namespace	Thread
{
  Cond::Cond()
  {
#if defined(WIN32)
    InitializeConditionVariable(&_c);
#elif defined(linux)
    pthread_cond_init(&_c, 0);
#else
# error "Unsupported Operating system"
#endif
  }

  Cond::~Cond()
  {

  }

  bool	Cond::broadcast()
  {
#if defined(WIN32)
    WakeAllConditionVariable(&_c);
#elif defined(linux)
    if (pthread_cond_broadcast(&_c) != 0)
      return (false);
#else
#error "Unsupported Operating system"
#endif
    return (true);
  }

  bool	Cond::signal()
  {
#if defined(WIN32)
    WakeConditionVariable(&_c);
#elif defined(linux)
    if (pthread_cond_signal(&_c) != 0)
      return (false);
#else
#error "Unsupported Operating system"
#endif
    return (true);
  }

  bool	Cond::wait(Mutex &m, msTime ms)
  {
#if defined(WIN32)
    if (ms == 0)
      {
	if (SleepConditionVariableCS(&_c, &m._m, INFINITE) != 0)
	  return (false);
      }
    else
      {
	if (SleepConditionVariableCS(&_c, &m._m, ms) != 0)
	  return (false);
      }
#elif defined(linux)
    if (ms == 0)
      {
	if (pthread_cond_wait(&_c, &m._m) != 0)
	  return (false);
      }
    else
      {
	struct timespec	sleepTime;

	sleepTime.tv_sec = ms / 1000;
	sleepTime.tv_nsec = (ms % 1000) * 1000000;
	if (pthread_cond_timedwait(&_c, &m._m, &sleepTime) != 0)
	  return (false);
      }
#else
#error "Unsupported Operating system"
#endif
    return (true);
  }
}
