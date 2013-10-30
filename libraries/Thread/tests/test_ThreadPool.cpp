#include	<iostream>
#if defined(WIN32)
#pragma comment(lib, "Threads.lib")
#endif
#include	"ThreadPool.hpp"

Thread::Mutex	m;

void	foo(int i)
{
  m.lock();
  std::cout << "current value: " << i << std::endl;
  m.unlock();
}

int					main()
{
  Thread::Pool		pool(4, 10, false);
  int					i = 0;

  pool.run();
  while (i < 10000)
    {
      pool.addWork(new Thread::Work<void (*)(int)>(Func::Bind(&foo, i)));
      ++i;
    }
  pool.stop(true);
  return (0);
}
