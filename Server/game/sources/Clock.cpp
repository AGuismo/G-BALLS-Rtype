#include	"Clock.h"

namespace	game
{
  Clock::Clock()
  {
  }

  Clock::~Clock()
  {
  }

  void		Clock::start()
  {
# if defined(WIN32)
    QueryPerformanceFrequency(&_procFreq);
    QueryPerformanceCounter(&_last);
#elif defined(linux)
    gettimeofday(&_last, 0);
# endif
  }

  void		Clock::update()
  {
    clock_time		elapsed_time;
# if defined(linux)
    struct timeval	current;
    struct timeval	*prev;

    prev = &_last;
    gettimeofday(&current, 0);
    elapsed_time = (current.tv_sec - prev->tv_sec) * CLOCK_PREC;
    elapsed_time += (current.tv_usec - prev->tv_usec);

#elif defined(WIN32)
    LARGE_INTEGER	current;
    LARGE_INTEGER	*prev;

    prev = &_last;
    QueryPerformanceCounter(&current);
    elapsed_time = ((current.QuadPart - prev->QuadPart) /
		    (_procFreq.QuadPart / CLOCK_PREC));

#endif
    _last = current;
    _elapsedTime = elapsed_time;
    _totalElapsedTime += elapsed_time;
  }
}
