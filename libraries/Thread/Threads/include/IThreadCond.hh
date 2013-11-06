#ifndef ITHREADCOND_H_
# define ITHREADCOND_H_

namespace	Thread
{
  class ICond
  {
    typedef int	msTime;
  public:
    virtual ~ICond() {}

  public:
    virtual bool	broadcast() = 0;
    virtual bool	signal() = 0;
    virtual bool	wait(IMutex &, msTime waitMaxDelay) = 0;
  };
}

#endif /* ITHREADCOND_H_ */
