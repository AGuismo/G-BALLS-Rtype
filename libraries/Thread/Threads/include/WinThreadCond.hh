//
// ThreadCond.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 13:13:42 2013 lambert kevin
// Last update Thu Dec 25 18:44:52 2014 lamber_k
//

#ifndef		WINTHREADCOND_HH_
# define	WINTHREADCOND_HH_

# include	<windows.h>
# include	<cstdint>
# include	"ThreadMutex.hh"
# include	"IThreadCond.hh"

namespace	Thread
{
  class	DECLPORT	Cond : public ICond
  {
  public:
    typedef size_t	msTime;

  private:
    CONDITION_VARIABLE	_c;

  public:
    Cond();
    virtual ~Cond();
    virtual bool	broadcast();
    virtual bool	signal();
    virtual bool	wait(Mutex &m);
    virtual bool	wait(Mutex &m, msTime msWait, bool &isTimeout);

    friend class	Mutex;
  };
};

#endif /* WINTHREADCOND_HH_ */
