#ifndef CLOCK_H_
# define CLOCK_H_

#if defined(linux)
# include	<sys/time.h>
#elif defined(WIN32)
# include	<windows.h>
#endif

class TimeConverter;


namespace	game
{
  class	Clock
  {
  public:
    typedef unsigned long long	clock_time;
  public:
    Clock();
    ~Clock();

    void		start();
    void		update();
    clock_time		getElapsedTime() const {return _elapsedTime;};
    clock_time		getTotalElapsedTime() const { return _totalElapsedTime;};

  private:

# if defined(WIN32)
    LARGE_INTEGER	_last;
    LARGE_INTEGER	_procFreq;
# elif defined(linux)
    struct timeval	_last;
#endif

    clock_time		_elapsedTime;
    clock_time		_totalElapsedTime;

    static const long CLOCK_PREC = 1000000;

    friend class TimeConverter;
  };
}
#endif /* CLOCK_H_ */
