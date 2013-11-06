#ifndef ITHREADMUTEX_H_
# define ITHREADMUTEX_H_

# include	"ThreadPlatform.hh"

namespace	Thread
{
  class DECLPORT IMutex
  {
  public:
    virtual ~IMutex() {}

  public:
    virtual bool	lock() = 0;
    virtual bool	unlock() = 0;
    virtual bool	trylock() = 0;
  };
}

#endif /* ITHREADMUTEX_H_ */
