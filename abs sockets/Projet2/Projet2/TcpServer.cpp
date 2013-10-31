#include "TcpServer.h"
using namespace net;

#if defined(WIN32)
#include "WinInit.h"
TcpServer::TcpServer()
{
	WinInit::GetInstance();
}

TcpServer::~TcpServer()
{

}

TcpServer::TcpServer(const TcpServer &src)
{

}

TcpServer	&TcpServer::operator=(TcpServer const &src)
{
  if (&src == this)
    {

    }
  return (*this);
}

SOCKET TcpServer::getSocket() const
{
	return _sock;
}


void			TcpServer::initialize(int port, int nbClients)
{
  int			test = 1;
  struct sockaddr_in	sin;

  _sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);
  if (_sock == -1)
    throw std::exception("socket");
  if (WSAHtonl(_sock, INADDR_ANY, &sin.sin_addr.s_addr) != 0)
	throw std::exception("WSAHtonll failed with error : " + WSAGetLastError());
  sin.sin_family = AF_INET;
	WSAHtons(_sock, port, &sin.sin_port);
  if (bind(_sock, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
    throw std::exception("bind");
  if (listen(_sock, nbClients) == -1)
    throw std::exception("listen");
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
TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{

}

TcpServer::TcpServer(const TcpServer &src)
{

}

TcpServer	&TcpServer::operator=(TcpServer const &src)
{
  if (&src == this)
    {

    }
  return (*this);
}

SOCKET TcpServer::getSocket() const
{
	return _sock;
}


void			TcpServer::initialize(int port, int nbClients)
{
  int			test = 1;
  struct sockaddr_in	sin;

  _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (_sock == -1)
    throw std::exception("socket");
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (bind(_sock, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
    throw std::exception("bind");
  if (listen(_sock, nbClients) == -1)
    throw std::exception("listen");
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
#endif