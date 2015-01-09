#pragma once

#if defined(linux)
# include	<sys/time.h>
#elif defined(WIN32)
# include	<windows.h>
#endif
#include	"Time.hh"

class Clock
{
public:
	Clock();
	~Clock();

	const Time	getElapsedTime() const;
	const Time	restart();

private:
# if defined(WIN32)
	LARGE_INTEGER	_last;
	LARGE_INTEGER	_procFreq;
# elif defined(linux)
	struct timeval	_last;
#endif
};