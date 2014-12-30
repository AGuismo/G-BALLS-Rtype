#pragma once

#include <string>
#include "ClientAccepted.h"
#include "abs_sockets.h"
#if defined(WIN32)
#include <Ws2tcpip.h>
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#endif

namespace net
{
  class ABS_SOCKET_API TcpClient : public ClientAccepted
  {
  public:
    TcpClient();
    ~TcpClient(void);
    void init(std::string adress, std::string port);
  };
}

