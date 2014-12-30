// Some Win/Linux Abstractions
#if defined(WIN32)
# include	<windows.h>
#elif defined(linux)
# include	<unistd.h>
#else
# error "Unsupported Operating System"
#endif

#include	"sys.hh"

namespace	sys
{

#if defined(WIN32)
  VOID	sleep(DWORD sec)
  {
    ::Sleep(sec * 1000);
  }

#elif defined(linux)
# include	<dlfcn.h>


  unsigned int	sleep(unsigned int sec)
  {
    return (::sleep(sec));
  }

#else
# error "Unsupported Operating System"
#endif

}
