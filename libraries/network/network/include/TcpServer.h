#pragma once

#if defined(WIN32)
#include <Winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "ClientAccepted.h"
#include "AMonitorable.h"
#include "abs_sockets.h"

namespace net
{
  class  ABS_SOCKET_API TcpServer : public AMonitorable
  {
  public:
    TcpServer();
    ~TcpServer();


  private:
    TcpServer(const TcpServer &src);
    TcpServer	&operator=(TcpServer const &src);

  public:
    void initialize(int port, int nbClients = 10);
    ClientAccepted *accept();

  private:
    SOCKET getSocket() const;

  private:
    SOCKET _sock;
    State  _state;
    struct sockaddr_in _addr;
  };
}
