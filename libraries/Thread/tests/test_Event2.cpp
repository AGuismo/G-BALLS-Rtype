#include	<iostream>
#include	<vector>
#include	<chrono> // C++11
#include	<ratio>
#if defined(WIN32)
#include	<windows.h>
#pragma comment(lib, "Threads.lib")
#elif defined(linux)
#include	<unistd.h>
#else
#error "Unsupported Operating System"
#endif
#include	"ThreadMutex.hh"
#include	"ThreadCond.hh"
#include	"ThreadEvent.hpp"
#include	"Threads.hpp"

using namespace std::chrono;

int			main()
{
  Thread::EventQueue<int *>	event;
  size_t			msWait = 20; // wake every 20ms
  bool				isTimeout = false;
  system_clock::time_point	start, after;
  duration<int,std::milli>	dif;

  for (int i = 0; i < 25; ++i)
  {
    start = system_clock::now();
    if (!event.pop(msWait, isTimeout) && !isTimeout)
    {
      std::cerr << "Wait() error" << std::endl;
      return (0);
    }
    if (!isTimeout)
      std::cerr << "No timeout, illogical" << std::endl;
    after = system_clock::now();
    dif = duration_cast<milliseconds>(after - start);
    std::cout << "Elapsed time " << dif.count()
	      << "ms - Expected ~" << msWait << "ms." << std::endl;
  }
}
