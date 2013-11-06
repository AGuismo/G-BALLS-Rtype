#include "TimeConverter.h"
#include "Clock.h"

TimeConverter::TimeConverter(void)
{
}


TimeConverter::~TimeConverter(void)
{
}

# if defined(WIN32)

	int TimeConverter::subTime(struct timeval *a, LARGE_INTEGER b)
	{
		struct timeval tmp;
		LARGE_INTEGER	tickPerSecond;

		QueryPerformanceFrequency(&tickPerSecond);
		tmp.tv_sec = b.QuadPart;
		tmp.tv_usec = (b.QuadPart * tickPerSecond.QuadPart) *
				(game::Clock::CLOCK_PREC / tickPerSecond.QuadPart); 

		if (a->tv_usec < tmp.tv_usec) {
			int nsec = (tmp.tv_usec - a->tv_usec) / 1000000 + 1;
			tmp.tv_usec -= 1000000 * nsec;
			tmp.tv_sec += nsec;
		}
		if (a->tv_usec - tmp.tv_usec > 1000000) {
			int nsec = (a->tv_usec - tmp.tv_usec) / 1000000;
			tmp.tv_usec += 1000000 * nsec;
			tmp.tv_sec -= nsec;
		}

		// Compute the time remaining to wait.
		// tv_usec is certainly positive. 
		a->tv_sec = a->tv_sec - tmp.tv_sec;
		a->tv_usec = a->tv_usec - tmp.tv_usec;

		// Return 1 if result is negative. 
		return a->tv_sec < tmp.tv_sec;
	}

	bool TimeConverter::isEqual(LARGE_INTEGER a, LARGE_INTEGER b)
	{
		if (a.QuadPart == b.QuadPart)
			return true;
		return false;
	}

	bool TimeConverter::isGreater(LARGE_INTEGER a, LARGE_INTEGER b)
	{
		return a.QuadPart > b.QuadPart;
	}

# elif defined(linux)

	void TimeConverter::subTime(struct timeval *a, struct timeval b)
	{
		struct timeval c;
		timersub(a, &b, &c);
		*a = c;
	}

	bool TimeConverter::isEqual(struct timeval a, struct timeval b)
	{
		return !timercmp(&a, &b, !=);
	}

	bool TimeConverter::isGreater(struct timeval a, struct timeval b)
	{
		return timercmp(&a, &b, >);
	}

#endif