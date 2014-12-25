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
#include	"ThreadMutex.hh"
#include	"ThreadCond.hh"
#include	"ThreadEvent.hpp"
#include	"Threads.hpp"

static Thread::EventQueue<int>	event;
static Thread::Mutex		disp;

void		producer(int id)
{
  while (true)
    {
      int	consumed = rand();

      if (event.push(new int(consumed)))
	{
	  disp.lock();
	  std::cerr << "Consumer{" << id << "}: send " << consumed
		    << "-" << event._stack.size() << std::endl;
	  disp.unlock();
	}
      else
	{
	  disp.lock();
	  std::cerr << "Consumer{" << id << "}: failed to send " << consumed << std::endl;
	  disp.unlock();
	}
#if defined(WIN32)
	  Sleep(10);
#elif defined(linux)
	  usleep(10000);
#else
#error "Unsupported Operating System"
#endif
    }
}

void		consumer(int id)
{
  while (true)
    {
      int	*ask;

      ask = event.pop();
      disp.lock();
      std::cerr << "Producer{" << id << "}: receive " << *ask
		<< "-" << event._stack.size() << std::endl;
      delete ask;
      disp.unlock();
      // sleep();
#if defined(WIN32)
	  Sleep(40);
#elif defined(linux)
	  usleep(40000);
#else
#error "Unsupported Operating System"
#endif
    }
}

int			main()
{
  Threads<void (*)(int)>	consumer1(Func::Bind(&consumer, 1));
  Threads<void (*)(int)>	consumer2(Func::Bind(&consumer, 2));
  Threads<void (*)(int)>	consumer3(Func::Bind(&consumer, 3));
  Threads<void (*)(int)>	consumer4(Func::Bind(&consumer, 4));
  Threads<void (*)(int)>	consumer5(Func::Bind(&consumer, 5));
  Threads<void (*)(int)>	producer1(Func::Bind(&producer, 1));
  Threads<void (*)(int)>	producer2(Func::Bind(&producer, 2));
  std::vector<Threads<void (*)(int)> *>	threads;

  threads.push_back(&consumer1);
  threads.push_back(&consumer2);
  threads.push_back(&consumer3);
  threads.push_back(&consumer4);
  threads.push_back(&consumer5);
  threads.push_back(&producer1);
  threads.push_back(&producer2);
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
  for (auto it = threads.begin(); it != threads.end(); ++it)
    {
      (*it)->cancel();
    }
  return (0);
}
