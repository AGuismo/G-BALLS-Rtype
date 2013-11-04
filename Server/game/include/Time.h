#pragma once

#include "types.hh"

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
  Rfloat f;
};

