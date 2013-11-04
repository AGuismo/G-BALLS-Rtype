#pragma once

#if defined(WIN32)
	#include <WinSock2.h>
	#include <time.h>
#elif defined(linux)
	#include <sys/time.h>
/*#else
	# error "Unsupported operating system"*/
#endif

#include "Entity.h"

class Action
{
public:
	Action(void);
	~Action(void);
	int init();
	int init_end();
	int check();
	int exec();

private:
	struct timeval	*_end;
	double			_time;
	Entity &		_launcher;
};