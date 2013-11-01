#pragma once

#include <vector>
#include <exception>
#include "AMonitorable.h"
#include "abs_sockets.h"
#if defined(WIN32)
#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "WSock32.lib")
#elif defined(linux)
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace net
{
#if defined(WIN32)
  EXMP template class ABS_SOCKET_API std::vector<AMonitorable *>;
#endif
  class ABS_SOCKET_API streamManager
  {
  public:
    enum Opt
    {
      NONBLOCK,
      TIMEOUT
    };

  public:
    streamManager();
    ~streamManager();

  public:
    void setOption(streamManager::Opt option, const struct timeval &timeout);
    void unsetOption(streamManager::Opt option);
    bool isOptionSet(streamManager::Opt option) const;
    void clear();
    void run();

    void setMonitor(AMonitorable &);
    void unsetMonitor(AMonitorable &);

    bool isTimeout() const;
    const struct timeval &getTimeval() const;

  private:
    bool	timeoutMode();

  private:
    timeval	_timeout;
    bool	_isTimeout;
    bool	_optTimeout;
    bool	_optNonBlocking;
    fd_set	_readMonitor;
    fd_set	_writeMonitor;
    SOCKET	_maxFd;
    std::vector<AMonitorable *>	_monitors;
  };
}
