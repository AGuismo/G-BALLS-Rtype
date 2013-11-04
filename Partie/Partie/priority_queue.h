#pragma once

#if defined(WIN32)
	#include <WinSock2.h>
	#include <time.h>
#elif defined(linux)
	#include <sys/time.h>
/*#else
	# error "Unsupported operating system"*/
#endif

#include <list>
#include "Action.h"

class priority_queue
{
public:
	priority_queue(void);
	~priority_queue(void);

	int init();
	int addAction(Action *ev);
	Action *calc();

private :
	struct  timeval		*_actual;
	struct  timeval		*_timeout;
	std::list<Action *>	_Actions;
};

