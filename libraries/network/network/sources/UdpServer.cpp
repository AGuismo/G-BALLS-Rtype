#include	"UdpServer.h"
#include	"NetException.h"

using namespace net;

#if defined(WIN32)
UdpServer::UdpServer(void)
{
  WinInit::GetInstance();
  monitor(true, true);
}


UdpServer::~UdpServer(void)
{
}

SOCKET UdpServer::getSocket() const
{
  return _sock;
}

void	UdpServer::setClientAddr(struct sockaddr_in s)
{
	_clientAddr = s;
}

struct sockaddr_in		UdpServer::getClientAddr() const
{
	return _clientAddr;
}

void UdpServer::initialize(int port, int nbClients)
{
  if((_sock = WSASocket(AF_INET , SOCK_DGRAM , IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
      throw net::Exception("WSASocket failed: ");
    }

  //Prepare the sockaddr_in structure
  _addr.sin_family = AF_INET;
  if (WSAHtonl(_sock, INADDR_ANY, &_addr.sin_addr.s_addr) != 0)
    throw net::Exception("WSAHtonll failed: ");
  WSAHtons(_sock, port, &_addr.sin_port);

  //Bind
  if( bind(_sock ,(struct sockaddr *)&_addr , sizeof(_addr)) == SOCKET_ERROR)
    {
      throw net::Exception("Bind failed: ");
    }
}

int			UdpServer::readData(char *data, int maxSize)
{
  DWORD		readSize = 0, flags = 0;
  WSABUF	wbuff;
  int		size = sizeof(_clientAddr);

  wbuff.buf = data;
  wbuff.len = maxSize;
  if (WSARecvFrom(_sock, &wbuff, 1, &readSize, &flags,
		  reinterpret_cast<sockaddr *>(&_clientAddr), &size, 0, 0) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("RecvFrom Failure: ");
    }
  if (readSize == 0)
    _state = DISCONNECTED;
  return (readSize);
}

int			UdpServer::writeData(const char *data, int size)
{
  WSABUF	wbuff;
  DWORD		writeSize;

  wbuff.buf = const_cast<char *>(data);
  wbuff.len = size;
  if (WSASendTo(_sock, &wbuff, 1, &writeSize, 0, reinterpret_cast<sockaddr *>(&_clientAddr),
		sizeof(_clientAddr), 0, 0) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("SendTo Failure: ");
    }
  if (writeSize == 0)
    {
      _state = DISCONNECTED;
      return (0);
    }
  return (writeSize);
}

void	UdpServer::close()
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

void	UdpServer::setClientAddr(struct sockaddr_in s)
{
	_clientAddr = s;
}

struct sockaddr_in		UdpServer::getClientAddr() const
{
	return _clientAddr;
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


int			UdpServer::readData(char *data, int maxSize)
{
  socklen_t		size = sizeof(_addr);
  int			readSize;

  readSize = recvfrom(_sock, data, maxSize, 0, reinterpret_cast<sockaddr *>(&_addr), &size);
  if (readSize == -1)
    {
      _state = STATEERROR;
      throw net::Exception("RecvFrom Failure: " + std::string(strerror(errno)));
    }
  if (readSize == 0)
    _state = DISCONNECTED;
  return (readSize);
}

int			UdpServer::writeData(const char *data, int size)
{
  int			writeSize;

  writeSize = sendto(_sock, data, size, 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  if (writeSize == -1)
    {
      _state = STATEERROR;
      throw net::Exception("SendTo Failure: " + std::string(strerror(errno)));
    }
  if (writeSize == 0)
    {
      _state = DISCONNECTED;
      return (0);
    }
  return (writeSize);
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

////////////////////////
// Shared with all os //
////////////////////////

bool	UdpServer::isOpen() const
{
  return (_state == CONNECTED);
}

bool	UdpServer::isClosed() const
{
  return (_state == CLOSED);
}

bool	UdpServer::isDisconnected() const
{
  return (_state == DISCONNECTED);
}

#include <iostream>

void UdpServer::recv()
{
  char			buff[512];
  int			count;
  //ClientAccepted	*c;

  count = readData(buff, 512);
  std::cout << "UdpServer::recv::count = " << count << std::endl;
  if (count <= 0)
    return /*(0)*/;
  //c = new ClientAccepted(_sock, _addr);
  for (int i = 0; i < count ; ++i)
    {
      _read.push(buff[i]);
      //c->_read.push(buff[i]);
    }
  //return (c);
}

void			UdpServer::send()
{
  cBuffer::stor_type	tmp;
  char			buf[512];
  int			size;
  cBuffer::size_type	count;

  count = _write.look(tmp, 512);
  for (cBuffer::size_type i = 0; i < count; ++i)
    buf[i] = tmp[i];
  if ((size = writeData(buf, count)) <= 0)
    return ;
  _write.read(tmp, size);
}

cBuffer::size_type UdpServer::readFromBuffer(cBuffer::stor_type &buf,
					     cBuffer::size_type count)
{
  return (_read.read(buf, count));
}

cBuffer::size_type UdpServer::writeIntoBuffer(const cBuffer::stor_type &buf,
					      cBuffer::size_type count)
{
  return (_write.write(buf, count));
}

cBuffer::size_type UdpServer::lookRead(cBuffer::stor_type &buf, cBuffer::size_type count)
{
  return _read.look(buf, count);
}

cBuffer::size_type UdpServer::lookWrite(cBuffer::stor_type &buf, cBuffer::size_type count)
{
  return _write.look(buf, count);
}
