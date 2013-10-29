#include	<iostream>
#include	<vector>
#if defined(WIN32)
#include	<windows.h>
#pragma comment(lib, "Threads.lib")
#elif defined(linux)
#include	<unistd.h>
#else
#error "Unsupported Operating System"
#endif
#include	<cstdlib>
#include	"ThreadMutex.hh"
#include	"ThreadCond.hh"
#include	"Threads.hpp"

static int			ressources = 20;
Thread::Mutex		locker;
Thread::Cond		cond_prod;
Thread::Cond		cond_cons;

void		producer(int id)
{
  while (true)
    {
      locker.lock();
      while (ressources > 0)
		cond_prod.wait(locker);
      ressources += 20;
      std::cout << "Producer{" << id << "}: send " << ressources << std::endl;
      cond_cons.signal();
      locker.unlock();
    }
}

void		consumer(int id)
{
  while (true)
    {
      locker.lock();
      while (ressources <= 0)
	  {
		  cond_prod.signal();
		  cond_cons.wait(locker);
	  }
      ressources--;
      std::cout << "Consumer{" << id << "}: consumed 1, stock: " << ressources << std::endl;
#if defined(WIN32)
	  Sleep(10);
#elif defined(linux)
	  usleep(10000);
#else
#error "Unsupported Operating System"
#endif
	  locker.unlock();
    }
}

int			main()
{
  Threads<void, int>	consumer1(&consumer, 1);
  Threads<void, int>	consumer2(&consumer, 2);
  Threads<void, int>	consumer3(&consumer, 3);
  Threads<void, int>	consumer4(&consumer, 4);
  Threads<void, int>	producer1(&producer, 1);
  std::vector<Threads<void, int> *>	threads;

  producer1.run();
  threads.push_back(&consumer1);
  threads.push_back(&consumer2);
  threads.push_back(&consumer3);
  threads.push_back(&consumer4);
  for (auto it = threads.begin(); it != threads.end(); ++it)
    {
      (*it)->run();
    }
#if defined(WIN32)
	  Sleep(10000);
#elif defined(linux)
	  sleep(10);
#else
#error "Unsupported Operating System"
#endif
  for (std::vector<Threads<void, int> *>::iterator it = threads.begin(); it != threads.end(); ++it)
    {
      (*it)->cancel();
    }
  return (0);
}
