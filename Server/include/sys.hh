#ifndef SYS_H_
# define SYS_H_

// Some Win/Linux Abstractions
#if defined(WIN32)
# include	<windows.h>
#elif defined(linux)
# include	<unistd.h>
#else
# error "Unsupported Operating System"
#endif

namespace	sys
{

#if defined(WIN32)
  VOID	sleep(DWORD sec);
#elif defined(linux)
  unsigned int	sleep(unsigned int sec);
#else
# error "Unsupported Operating System"
#endif

}

#endif /* SYS_H_ */
