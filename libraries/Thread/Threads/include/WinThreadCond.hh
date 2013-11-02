//
// ThreadCond.hh for thread in /home/lamber_k/Dropbox/Projects/module_4e_sem/plazza/include
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Mon Apr 15 13:13:42 2013 lambert kevin
// Last update Fri Nov  1 22:25:32 2013 lambert kevin
//

#ifndef		WINTHREADCOND_HH_
# define	WINTHREADCOND_HH_

# include	<windows.h>
# include	<cstdint>
# include	"WinThreadMutex.hh"

namespace	Thread
{
  class	DECLPORT	Cond
  {
  public:
	typedef uint32_t	msTime;

  private:
    CONDITION_VARIABLE	_c;

  public:
    Cond();
    virtual ~Cond();
    virtual bool	broadcast();
    virtual bool	signal();
    virtual bool	wait(Mutex &_m, msTime = 0);

    friend class	Mutex;
  };
};

#endif /* WINTHREADCOND_HH_ */
