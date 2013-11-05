#pragma once

#if defined(linux)
# include	<sys/time.h>
#elif defined(WIN32)
# include	<windows.h>
#endif

class TimeConverter
{
public:
	TimeConverter(void);
	~TimeConverter(void);

# if defined(WIN32)
	static int subTime(struct timeval *a, LARGE_INTEGER b);
	static bool isEqual(LARGE_INTEGER a, LARGE_INTEGER b);
	static bool isGreater(LARGE_INTEGER a, LARGE_INTEGER b);
# elif defined(linux)
	static void subTime(struct timeval *a, struct timeval b);
	static bool isEqual(struct timeval a, struct timeval b);
	static bool isGreater(struct timeval a, struct timeval b);

#endif
};

