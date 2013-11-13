//
// ThreadMutex.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 13:07:15 2013 lambert kevin
// Last update Wed Nov  6 18:54:28 2013 lambert kevin
//

#ifndef		THREADMUTEX_HH_
# define	THREADMUTEX_HH_

# include	<pthread.h>
# include	"IThreadMutex.hh"

namespace	Thread
{
  class MutexBase
  {
  protected:
    pthread_mutex_t		_m;

  public:
    MutexBase()
    {
      pthread_mutex_init(&_m, NULL);
    }
    virtual ~MutexBase()
    {
      pthread_mutex_destroy(&_m);
    }
  };

  class				Mutex : protected MutexBase, public IMutex
  {
  public:
    Mutex();
    virtual ~Mutex();
    virtual bool		lock();
    virtual bool		unlock();
    virtual bool		trylock();

  protected:
    pthread_mutex_t		&getMutex();

    friend class	Cond;
  };

  class				MutexGuard
  {
    Mutex			&_locker;

  public:
    MutexGuard(Mutex &);
    virtual ~MutexGuard();

    friend class	Mutex;
  };
};
#endif /* THREADMUTEX_HH_ */
