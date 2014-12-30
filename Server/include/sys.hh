#ifndef SYS_H_
# define SYS_H_

namespace	sys
{

#if defined(WIN32)
  void	sleep(unsigned long sec);
#elif defined(linux)
  unsigned int	sleep(unsigned int sec);
#else
# error "Unsupported Operating System"
#endif

}

#endif /* SYS_H_ */
