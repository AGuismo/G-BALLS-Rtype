//
// ThreadCond.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 13:13:42 2013 lambert kevin
// Last update Thu Dec 25 19:18:19 2014 lamber_k
//

#ifndef		THREADCOND_HH_
# define	THREADCOND_HH_

# include	<pthread.h>
# include	<cstddef>
# include	"ThreadMutex.hh"
# include	"IThreadCond.hh"

namespace	Thread
{
  class		Cond : public ICond
  {
  public:
    typedef ICond::msTime	msTime;

  private:
    pthread_cond_t	_c;

  public:
    Cond();
    virtual ~Cond();
    virtual bool	broadcast();
    virtual bool	signal();
    virtual bool	wait(Mutex &m);
    virtual bool	wait(Mutex &m, msTime msWait, bool &isTimeout);
    static Cond		*createCond();

    friend class	Mutex;
  };
};

#endif /* THREADCOND_HH_ */
