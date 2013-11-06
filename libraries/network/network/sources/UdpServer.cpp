#include "UdpServer.h"
#include "NetException.h"

using namespace net;

#if defined(WIN32)
UdpServer::UdpServer(void)
{
  WinInit::GetInstance();
  monitor(true, false);
}


UdpServer::~UdpServer(void)
{
}

SOCKET UdpServer::getSocket() const
{
  return _sock;
}

void UdpServer::initialize(int port, int nbClients)
{
  if((_sock = WSASocket(AF_INET , SOCK_DGRAM , IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
      throw net::Exception("WSASocket failed: " + WSAGetLastError());
    }

  //Prepare the sockaddr_in structure
  _addr.sin_family = AF_INET;
  if (WSAHtonl(_sock, INADDR_ANY, &_addr.sin_addr.s_addr) != 0)
    throw net::Exception("WSAHtonll failed: " + WSAGetLastError());
  WSAHtons(_sock, port, &_addr.sin_port);

  //Bind
  if( bind(_sock ,(struct sockaddr *)&_addr , sizeof(_addr)) == SOCKET_ERROR)
    {
      throw net::Exception("Bind failed: " + WSAGetLastError());
    }
}

ClientAccepted *UdpServer::recv()
{
  DWORD						count = 0, flags = 0;
  WSABUF						wbuff;
  char						buff[512];
  std::vector<cBuffer::Byte>	tmp;
  int  size = sizeof(_addr);


  wbuff.buf = buff;
  wbuff.len = 512;
  WSARecvFrom(_sock, &wbuff, 1, &count, &flags, reinterpret_cast<sockaddr *>(&_addr), &size, NULL, NULL);
  for (unsigned int i = 0; i < wbuff.len ; i++)
    tmp.insert(tmp.end(), wbuff.buf[i]);
  _read.write(tmp, size);
  return new ClientAccepted(_sock, _addr);
}

void UdpServer::send()
{
  SSIZE_T				count, n;
  std::vector<cBuffer::Byte>		tmp;
  char	buf[512];
  WSABUF	wbuff;
  DWORD		size;
  int i;

  count = _write.look(tmp, 512);
  for (i = 0; i < count ; i++)
    buf[i] = tmp[i];
  wbuff.buf = buf;
  wbuff.len = i;
  n = WSASendTo(_sock, &wbuff, 1, &size, MSG_OOB, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr), NULL, NULL);
  if (n == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Recv Failure: " + WSAGetLastError());
    }
  if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  _write.read(tmp, size);
}

void UdpServer::close()
{
  if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure: " + WSAGetLastError());
    }
  _state = DISCONNECTED;
  _sock = 0;
}

#elif defined(linux)

#include	<errno.h>
#include	<cstring>
#include	<unistd.h>

UdpServer::UdpServer(void)
{
  monitor(true, false);
}


UdpServer::~UdpServer(void)
{
}

SOCKET UdpServer::getSocket() const
{
  return _sock;
}

void UdpServer::initialize(int port, int nbClients)
{
  (void)nbClients;
  if((_sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP)) == -1)
    {
      throw net::Exception("Socket failed: " + std::string(strerror(errno)));
    }

  //Prepare the sockaddr_in structure
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = htonl(INADDR_ANY);
  _addr.sin_port = htons(port);
  //Bind
  if(bind(_sock ,(struct sockaddr *)&_addr , sizeof(_addr)) == -1)
    {
      throw net::Exception("Bind failed: " + std::string(strerror(errno)));
    }
}

ClientAccepted *UdpServer::recv()
{
  int				count = 0, flags = 0;
  char				buff[512];
  std::vector<cBuffer::Byte>	tmp;
  socklen_t			size = sizeof(_addr);
  ssize_t			ret;

  ClientAccepted *client;

  ret = recvfrom(_sock, buff, count, flags, reinterpret_cast<sockaddr *>(&_addr), &size);
  for (ssize_t i = 0; i < ret ; i++)
    tmp.insert(tmp.end(), buff[i]);
  _read.write(tmp, size);
  client = new ClientAccepted(_sock, _addr);
  return client;
}

void UdpServer::send()
{
  ssize_t				count, n;
  std::vector<cBuffer::Byte>		tmp;
  char	buf[512];
  int i;

  count = _write.look(tmp, 512);
  for (i = 0; i < count ; i++)
    buf[i] = tmp[i];
  n = sendto(_sock, buf, i, MSG_OOB, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  if (n == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Recv Failure: " + std::string(strerror(errno)));
    }
  if (n == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  _write.read(tmp, n);
}

void UdpServer::close()
{
  if (::close(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure: " + std::string(strerror(errno)));
    }
  _state = DISCONNECTED;
  _sock = 0;
}
#endif

cBuffer::size_type UdpServer::readFromBuffer(std::vector<cBuffer::Byte> &buf,
					     cBuffer::size_type count)
{
  return (_read.read(buf, count));
}

cBuffer::size_type UdpServer::writeIntoBuffer(const std::vector<cBuffer::Byte> &buf,
					      cBuffer::size_type count)
{
  return (_write.write(buf, count));
}

cBuffer::size_type UdpServer::lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
  return _read.look(buf, count);
}

cBuffer::size_type UdpServer::lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
  return _write.look(buf, count);
}
