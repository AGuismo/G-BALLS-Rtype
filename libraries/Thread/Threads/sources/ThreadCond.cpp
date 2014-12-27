//
// ThreadCond.cpp for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/sources
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 14:22:56 2013 lambert kevin
// Last update Thu Dec 25 19:47:09 2014 lamber_k
//

#include	<iostream>
#include	"ThreadCond.hh"
#include	"ThreadMutex.hh"
#if defined(linux)
# include	<errno.h>
# include	<sys/time.h>
#endif


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

  bool	Cond::wait(Mutex &m, msTime maxWait_ms, bool &isTimeout)
  {
#if defined(WIN32)
    bool	res;

    if (maxWait_ms == 0)
      res = SleepConditionVariableCS(&_c, &m._m, INFINITE);
    else
      res = SleepConditionVariableCS(&_c, &m._m, maxWait_ms);

    if (!res && GetLastError() == ERROR_TIMEOUT)
      isTimeout = true;
    else
      isTimeout = false;
    return (res);

#elif defined(linux)
    int		res;

    if (maxWait_ms == 0)
      res = pthread_cond_wait(&_c, &m._m);
    else
      {
	struct timespec	sleepTime;
	struct timeval	now;

	gettimeofday(&now,NULL);


	sleepTime.tv_sec = now.tv_sec + maxWait_ms / 1000;
	sleepTime.tv_nsec = (now.tv_usec + 1000UL*maxWait_ms)*1000UL;
	if (sleepTime.tv_nsec > 1000000000L)
	{
	  sleepTime.tv_sec += (sleepTime.tv_nsec / 1000000000UL);
	  sleepTime.tv_nsec -= ((sleepTime.tv_nsec / 1000000000UL) * 1000000000UL);
	}
	res = pthread_cond_timedwait(&_c, &m._m, &sleepTime);
      }

    if (res == ETIMEDOUT)
      isTimeout = true;
    else
      isTimeout = false;
    return (res == 0);

#else
#error "Unsupported Operating system"
#endif
  }

  bool	Cond::wait(Mutex &m)
  {
#if defined(WIN32)

    return (SleepConditionVariableCS(&_c, &m._m, INFINITE));

#elif defined(linux)

    return (pthread_cond_wait(&_c, &m._m) == 0);

#else
#error "Unsupported Operating system"
#endif
  }
}
