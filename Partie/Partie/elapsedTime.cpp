#include "elapsedTime.h"

ElapsedTime::ElapsedTime(void)
{
}


ElapsedTime::~ElapsedTime(void)
{
}

void ElapsedTime::start()
{
# if defined(WIN32)
    QueryPerformanceFrequency(&_procFreq);
    QueryPerformanceCounter(&_begin);
#elif defined(linux)
    gettimeofday(&_begin, &_tz);
# endif
}

void ElapsedTime::stop()
{
# if defined(WIN32)
    QueryPerformanceCounter(&_end);
    _time = double(_end.QuadPart - _begin.QuadPart) / (_procFreq.QuadPart / 1000000.0);
#elif defined(linux)
    gettimeofday(&_end, &_tz);
    _time = (_end.tv_sec - _begin.tv_sec) *
      1000000L + (_end.tv_usec - _begin.tv_usec);
# endif
}