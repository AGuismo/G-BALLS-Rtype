//
// ThreadMutex.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 13:07:15 2013 lambert kevin
// Last update Wed Nov  6 18:50:24 2013 lambert kevin
//

#ifndef		WINTHREADMUTEX_HH_
# define	WINTHREADMUTEX_HH_

# include	"ThreadPlatform.hh"
# include	"IThreadMutex.hh"
# include	<windows.h>

namespace 	Thread
{
  class DECLPORT MutexBase
  {
  protected:
    CRITICAL_SECTION	_m;

  public:
	MutexBase();
	virtual ~MutexBase();
  };

  class	DECLPORT 		Mutex : protected MutexBase, public IMutex
  {
  public:
    Mutex();
    virtual ~Mutex();
    virtual bool		lock();
    virtual bool		unlock();
    virtual bool		trylock();
    static Thread::Mutex	*createMutex();

  protected:
    CRITICAL_SECTION	&getMutex();
    friend class	Cond;
  };

  class	DECLPORT 	MutexGuard
  {
    Mutex		&_locker;

  public:
    MutexGuard(Mutex &);
    virtual ~MutexGuard();

    friend class	Mutex;
  };
};
#endif /* WINTHREADMUTEX_HH_ */
