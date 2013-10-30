#include	"sys.hh"

namespace	sys
{

#if defined(WIN32)
  VOID	sleep(DWORD sec)
  {
    ::Sleep(sec * 1000);
  }

#elif defined(linux)
  unsigned int	sleep(unsigned int sec)
  {
    return (::sleep(sec));
  }
#else
# error "Unsupported Operating System"
#endif

}
