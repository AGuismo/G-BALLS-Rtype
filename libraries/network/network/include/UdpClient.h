#pragma once

#if defined(WIN32)
#include <Ws2tcpip.h>
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#endif
#include <sstream>
#include "ClientAccepted.h"

namespace net
{
  class UdpClient : public ClientAccepted
  {
  public:
    UdpClient(void);
    ~UdpClient(void);
    void init(std::string adress, std::string port);
  };
}
