#pragma once

#include "Types.h"

class Time
{
public:
	Time(void);
# if defined(linux)
	Time(struct timeval t);
# elif defined(WIN32)
	Time(LARGE_INTEGER t);
#endif
	~Time(void);

private:
	RFloat f;
};

