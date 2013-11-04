#ifndef ELAPSEDTIME_H_
# define ELAPSEDTIME_H_
 
# if defined(WIN32)
#  include <windows.h>
# elif defined(linux)
#  include <ctime>
#  include <sys/time.h>
/*# else
# error "Unsupported operating system"*/
# endif
 
class ElapsedTime
{
public:
  ElapsedTime(); 
  ~ElapsedTime();

  void start();
  void stop();
  long getElapsedTime() const{return _time;};
 
private:
  long _time;
 
# ifdef WIN32
  LARGE_INTEGER _begin, _end;
  LARGE_INTEGER _procFreq;
#elif defined(linux)
  struct timeval _begin, _end;
  struct timezone _tz;
# endif
};
 
#endif /* !ELAPSEDTIME_HH_ */