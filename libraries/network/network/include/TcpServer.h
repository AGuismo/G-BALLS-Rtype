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

namespace net
{
  class TcpServer : public AMonitorable
  {
  public:
    TcpServer();
    ~TcpServer();

  public:
    void		initialize(unsigned short int port, int maxPendingConnections = 10);
    ClientAccepted	*accept();

  public:
    short int		getPort() const;
    int			getMaxPendingConnections() const;

  private:
    TcpServer(const TcpServer &src);
    TcpServer	&operator=(TcpServer const &src);

  private:
    SOCKET getSocket() const;

  private:
    SOCKET		_sock;
    State		_state;
    struct sockaddr_in	_addr;
    unsigned short int	_port;
    int			_maxPendingConnections;
  };
}
