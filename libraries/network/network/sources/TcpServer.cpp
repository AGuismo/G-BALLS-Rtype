#include "TcpServer.h"
#include "NetException.h"

using namespace net;

#if defined(WIN32)

# include "WinInit.h"

TcpServer::TcpServer()
{
  WinInit::GetInstance();
}

TcpServer::~TcpServer()
{

}

SOCKET TcpServer::getSocket() const
{
  return _sock;
}

void			TcpServer::initialize(unsigned short int port, int maxPendingConnections)
{
  int			test = 1;
  struct sockaddr_in	sin;

  _maxPendingConnections = maxPendingConnections;
  _port = port;
  _sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);
  if (_sock == -1)
    throw net::Exception("socket: " + WSAGetLastError());
  if (WSAHtonl(_sock, INADDR_ANY, &sin.sin_addr.s_addr) != 0)
    throw net::Exception("WSAHtonll failed with error : " + WSAGetLastError());
  sin.sin_family = AF_INET;
  WSAHtons(_sock, port, &sin.sin_port);
  if (bind(_sock, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
    throw net::Exception("bind error: " + WSAGetLastError());
  if (listen(_sock, maxPendingConnections) == -1)
    throw net::Exception("listen error: " + WSAGetLastError());
  _state = CONNECTED;
}

ClientAccepted	*TcpServer::accept()
{
  SOCKET				newSock;
  struct sockaddr_in	csin;
  int		len = sizeof(csin);
  ClientAccepted		*dest;

  newSock = ::accept(_sock, reinterpret_cast<struct sockaddr *>(&csin), &len);
  dest = new ClientAccepted(newSock, csin);
  return dest;
}
#elif defined(linux)
# include	<errno.h>
# include	<cstring>

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{

}

SOCKET TcpServer::getSocket() const
{
  return _sock;
}


void			TcpServer::initialize(unsigned short int port, int maxPendingConnections)
{
  struct sockaddr_in	sin;

  _maxPendingConnections = maxPendingConnections;
  _port = port;
  _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (_sock == -1)
    throw net::Exception("socket error: " + std::string(strerror(errno)));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (bind(_sock, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
    throw net::Exception("bind error: " + std::string(strerror(errno)));
  if (listen(_sock, maxPendingConnections) == -1)
    throw net::Exception("listen error: " + std::string(strerror(errno)));
  _state = CONNECTED;
}

ClientAccepted		*TcpServer::accept()
{
  SOCKET		newSock;
  struct sockaddr_in	csin;
  socklen_t		len = sizeof(csin);
  ClientAccepted	*dest;

  newSock = ::accept(_sock, reinterpret_cast<struct sockaddr *>(&csin), &len);
  dest = new ClientAccepted(newSock, csin);
  return dest;
}
#endif

short int		TcpServer::getPort() const
{
  return (_port);
}

int			TcpServer::getMaxPendingConnections() const
{
  return (_maxPendingConnections);
}
