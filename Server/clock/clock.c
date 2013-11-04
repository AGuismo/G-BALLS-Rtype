#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"clock.h"
#include	"error.h"

gameClock::gameClock()
{
}

gameClock::~gameClock()
{
}

void		gameClock::start()
{
# if defined(WIN32)
    QueryPerformanceFrequency(&_procFreq);
    QueryPerformanceCounter(&_last);
#elif defined(linux)
    gettimeofday(&_last, NULL);
# endif 
}

void		gameClock::update()
{
	float			elapsed_time;
# if defined(linux)
	struct timeval	current;
	struct timeval	*prev;

	prev = &_last;
	gettimeofday(&current, NULL);
	elapsed_time = (current.tv_sec - prev->tv_sec) * CLOCK_PREC;
	elapsed_time += (current.tv_usec - prev->tv_usec);

#elif defined(WIN32)
	LARGE_INTEGER	current;
	LARGE_INTEGER	*prev;
	
	prev = &_last;
	QueryPerformanceCounter(&current);
	elapsed_time = (current.QuadPart - prev.QuadPart) /
					(_procFreq.QuadPart / CLOCK_PREC);
	
#endif
	_last = current;
	_elapsed_time = elapsed_time;
	_total_elapsed_time += elapsed_time;
}
