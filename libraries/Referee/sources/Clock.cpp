#include	"Clock.hh"

Clock::Clock()
{
# if defined(WIN32)
	QueryPerformanceFrequency(&_procFreq);
	QueryPerformanceCounter(&_last);
#elif defined(linux)
	gettimeofday(&_last, 0);
# endif
}

Clock::~Clock()
{

}

#if defined(WIN32)
const Time	Clock::getElapsedTime() const
{
	LARGE_INTEGER	current;

	QueryPerformanceCounter(&current);
	return (Time::microseconds((current.QuadPart - _last.QuadPart) * 1000000L / _procFreq.QuadPart));
}

const Time	Clock::restart()
{
	LARGE_INTEGER	current;
	Time			t;

	QueryPerformanceCounter(&current);
	t = Time::microseconds((current.QuadPart - _last.QuadPart) * 1000000L / _procFreq.QuadPart);
	_last = current;
	return (t);
}

#elif defined(linux)

const Time	Clock::getElapsedTime() const
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (Time::microseconds((current.tv_sec - _last.tv_sec) * 1000000L + (current.tv_usec - _last.tv_usec)));
}

const Time	Clock::restart()
{
	struct timeval	current;
	Time			t;

	gettimeofday(&current, 0);
	t = Time::microseconds((current.tv_sec - _last.tv_sec) * 1000000L + (current.tv_usec - _last.tv_usec));
	_last.tv_sec = current.tv_sec;
	_last.tv_usec = current.tv_usec;
	return (t);
}

# endif
