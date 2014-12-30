#pragma once

#include <string>
#include "ClientAccepted.h"
#if defined(WIN32)
#include <Ws2tcpip.h>
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#endif

namespace net
{
  class TcpClient : public ClientAccepted
  {
  public:
    TcpClient();
    ~TcpClient(void);
    void init(std::string adress, std::string port);
  };
}

