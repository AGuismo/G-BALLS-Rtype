#ifndef ITHREADCOND_H_
# define ITHREADCOND_H_

# include	"ThreadPlatform.hh"

namespace	Thread
{
  class DECLPORT ICond
  {
  protected:
    typedef size_t	msTime;
  public:
    virtual ~ICond() {}

  public:
    virtual bool	broadcast() = 0;
    virtual bool	signal() = 0;
    virtual bool	wait(Mutex &m) = 0;
    virtual bool	wait(Mutex &m, msTime waitMaxDelay, bool &isTimeout) = 0;
  };
}

#endif /* ITHREADCOND_H_ */
