#include	"ClientAccepted.h"
#include	"NetException.h"
#include	<iostream>
#include	<exception>

using namespace net;

#if defined(WIN32)
ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr)
{
  WinInit::GetInstance();
  _sock = sock;
  _addr = addr;
  _state = CONNECTED;
}

ClientAccepted::ClientAccepted()
{
  WinInit::GetInstance();
}

ClientAccepted::~ClientAccepted()
{
  close();
}

int			UdpServer::readData(char *data, int maxSize)
{
  DWORD		readSize = 0, flags = 0;
  WSABUF	wbuff;
  int		size = sizeof(_addr);

  wbuff.buf = data;
  wbuff.len = maxSize;
  if (WSARecvFrom(_sock, &wbuff, 1, &readSize, &flags,
		  reinterpret_cast<sockaddr *>(&_addr), &size, 0, 0) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("RecvFrom Failure: " + WSAGetLastError());
    }
  if (readSize == 0)
    _state = DISCONNECTED;
  return (readSize);
}

int			UdpServer::writeData(const char *data, int size)
{
  WSABUF	wbuff;
  DWORD		writeSize;

  wbuff.buf = data;
  wbuff.len = size;
  if (WSASendTo(_sock, &wbuff, 1, &writeSize, 0, reinterpret_cast<sockaddr *>(&_addr),
		sizeof(_addr), 0, 0) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("SendTo Failure: " + WSAGetLastError());
    }
  if (writeSize == 0)
    {
      _state = DISCONNECTED;
      return (0);
    }
  _write.read(tmp, writeSize);
  return (writeSize);
}

// int				ClientAccepted::recv()
// {
//   DWORD				count, flags = MSG_PARTIAL;
//   WSABUF			wbuff;
//   char				c[512];
//   std::vector<cBuffer::Byte>	tmp;
//   int				size = sizeof(_addr);

//   std::cout << "In ClientAccepted::recv"  << std::endl;
//   wbuff.buf = c;
//   wbuff.len = 512;
//   std::cout << "receiving ..." << std::endl;
//   if (WSARecvFrom(_sock, &wbuff, 1, &count, &flags,
// 		  reinterpret_cast<sockaddr *>(&_addr),
// 		  &size, NULL, NULL) == SOCKET_ERROR)
//     {
//       _state = STATEERROR;
//       throw net::Exception("Recv Failure");
//     }
//   if (count == 0)
//   {
// 	  _state = DISCONNECTED;
// 	  return (0);
//   }
//   std::cout << "count : " << count << std::endl;
//   for (DWORD i = 0; i < count; i++)
//   {
// //	  std::cout << "i : " << i << std::endl;
// 	  tmp.insert(tmp.end(), wbuff.buf[i]);
//   }
//   _read.write(tmp, count);
//   std::cout << "return" << std::endl;
//   return (count);
// }

// int				ClientAccepted::send()
// {
//   SSIZE_T			n;
//   DWORD				count, i;
//   std::vector<cBuffer::Byte>	tmp;
//   char				buf[512];
//   WSABUF			wbuff;

//   count = (DWORD)_write.look(tmp, 512);
//   for (i = 0; i < count ; i++)
//     buf[i] = tmp[i];
//   wbuff.buf = buf;
//   wbuff.len = i;
//   n = WSASendTo(_sock, &wbuff, 1, &count, MSG_OOB,
// 		reinterpret_cast<sockaddr *>(&_addr),
// 		sizeof(_addr), NULL, NULL);
//   if (n == SOCKET_ERROR)
//     {
//       _state = STATEERROR;
//       throw net::Exception("Send Failure");
//     }
//   if (count == 0)
//     {
//       _state = DISCONNECTED;
//       return (0);
//     }
//   _write.read(tmp, count);
//   if (_write.empty())
//     monitor(true, false);
//   return (count);
// }

void ClientAccepted::close()
{
  if (_state == CLOSED || _state == STATEERROR)
    return ;
  if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure");
    }
  _state = CLOSED;
  _sock = 0;
}

SOCKET		ClientAccepted::getSocket()const
{
  return _sock;
}

#elif defined(linux)

#include	<unistd.h>
#include	<errno.h>
#include	<cstring>
#include	<string>

ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr) :
  AMonitorable(true, false)
{
  _sock = sock;
  _addr = addr;
  _state = CONNECTED;
}

ClientAccepted::ClientAccepted()
{
}

ClientAccepted::~ClientAccepted()
{
  close();
}

int		ClientAccepted::readData(char *data, int maxSize)
{
  socklen_t	size = sizeof(_addr);
  int		readSize;

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

int		ClientAccepted::writeData(const char *data, int size)
{
  int		writeSize;

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

void		ClientAccepted::close()
{
  if (::close(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure: " + std::string(strerror(errno)));
    }
  _state = DISCONNECTED;
  _sock = 0;
}

// int				ClientAccepted::recv()
// {
//   int				count = 512;
//   char				buf[512];
//   std::vector<cBuffer::Byte>	tmp;
//   socklen_t			size = sizeof(_addr);
//   ssize_t			readSize;

//   readSize = recvfrom(_sock, buf, count, 0, reinterpret_cast<sockaddr *>(&_addr), &size);
//   if (readSize == -1)
//     {
//       _state = STATEERROR;
//       throw net::Exception("Recvfrom Failure" + std::string(strerror(errno)));
//     }
//   if (readSize == 0)
//     {
//       _state = DISCONNECTED;
//       return (readSize);
//     }
//   for (socklen_t i = 0; i < readSize ; i++)
//     tmp.insert(tmp.end(), buf[i]);
//   _read.write(tmp, readSize);
//   return (readSize);
// }

// int					ClientAccepted::send()
// {
//   ssize_t				count, n;
//   std::vector<cBuffer::Byte>		tmp;
//   char					buf[512];

//   count = _write.look(tmp, 512);
//   for (ssize_t i = 0; i < count ; i++)
//     buf[i] = tmp[i];
//   n = sendto(_sock, buf, count, 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
//   if (n == -1)
//     {
//       _state = STATEERROR;
//       throw net::Exception("Sendto Failure" + std::string(strerror(errno)));
//     }
//   else if (n == 0)
//     {
//       _state = DISCONNECTED;
//       return (n);
//     }
//   _write.read(tmp, n);
//   if (_write.empty())
//     monitor(true, false);
//   return (n);
// }

SOCKET		ClientAccepted::getSocket()const
{
  return _sock;
}

#endif

bool			ClientAccepted::isOpen() const
{
  return (_state == CONNECTED);
}

bool			ClientAccepted::isDisconnected() const
{
  return (_state == DISCONNECTED);
}

bool			ClientAccepted::isClosed() const
{
  return (_state == CLOSED);
}

int			ClientAccepted::recv()
{
  char			buf[512];
  int			readSize;

  readSize = readData(buf, 512);
  if (readSize <= 0)
    return (readSize);
  for (int i = 0; i < readSize ; ++i)
    _read.push(buf[i]);
  return (readSize);
}

int			ClientAccepted::send()
{
  cBuffer::stor_type	tmp;
  char			buf[512];
  int			size;
  cBuffer::size_type	count;

  count = _write.look(tmp, 512);
  for (cBuffer::size_type i = 0; i < count; ++i)
    buf[i] = tmp[i];
  if ((size = writeData(buf, count)) <= 0)
    return (size);
  _write.read(tmp, size);
  if (_write.empty())
    monitor(true, false);
  return (size);
}

cBuffer::size_type	ClientAccepted::readFromBuffer(std::vector<cBuffer::Byte> &buf,
						       cBuffer::size_type count)
{
  return (_read.read(buf, count));
}

cBuffer::size_type	ClientAccepted::writeIntoBuffer(const std::vector<cBuffer::Byte> &buf,
						   cBuffer::size_type count)
{
  monitor(true, true);
  return (_write.write(buf, count));
}

cBuffer::size_type	ClientAccepted::lookRead(std::vector<cBuffer::Byte> &buf,
						 cBuffer::size_type count)
{
  return _read.look(buf, count);
}

cBuffer::size_type	ClientAccepted::lookWrite(std::vector<cBuffer::Byte> &buf,
						  cBuffer::size_type count)
{
  return _write.look(buf, count);
}
