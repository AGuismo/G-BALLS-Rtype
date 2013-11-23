#include	"ClientAccepted.h"
#include	"NetException.h"
#include	<iostream>
#include	<exception>

using namespace net;

#if defined(WIN32)
ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr) :
  AMonitorable(true, false)
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
  try
    {
      close();
    }
  catch (net::Exception &e)
    {
      std::cerr << "Failed to close ClientAccepted : " << e.what() << std::endl;
    }
}

int			ClientAccepted::readData(char *data, int maxSize)
{
  DWORD		readSize = 0, flags = 0;
  WSABUF	wbuff;
  int		size = sizeof(_addr);

  if (_state != CONNECTED)
    return (0);
  wbuff.buf = data;
  wbuff.len = maxSize;
  if (WSARecvFrom(_sock, &wbuff, 1, &readSize, &flags,
		  reinterpret_cast<sockaddr *>(&_addr), &size, 0, 0) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("RecvFrom Failure: " + WSAGetLastError());
    }
  std::cout << "readData::readSize = " << readSize << std::endl;
  if (readSize == 0)
    _state = DISCONNECTED;
  return (readSize);
}

int			ClientAccepted::writeData(const char *data, int size)
{
  WSABUF	wbuff;
  DWORD		writeSize;

  if (_state != CONNECTED)
    return (0);
  wbuff.buf = const_cast<char *>(data);
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
  return (writeSize);
}

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
  _state = CONNECTED;
}

ClientAccepted::~ClientAccepted()
{
  try
    {
      close();
    }
  catch (net::Exception &e)
    {
      std::cerr << "Failed to close ClientAccepted : " << e.what() << std::endl;
    }
}

int		ClientAccepted::readData(char *data, int maxSize)
{
  socklen_t	size = sizeof(_addr);
  int		readSize;

  if (_state != CONNECTED)
    return (0);
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

  if (_state != CONNECTED)
    return (0);
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
  _state = CLOSED;
  _sock = 0;
}

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
  std::cout << "ReadSize = " << readSize << std::endl;
  if (readSize <= 0)
    return (readSize);
  for (int i = 0; i < readSize ; ++i)
    _read.push(buf[i]);
  return (readSize);
}

int			ClientAccepted::send()
{
  cBuffer::stor_type	tmp;
  char			buf[512] = {0};
  int			size;
  cBuffer::size_type	count;

  count = _write.look(tmp, 512);
  for (cBuffer::size_type i = 0; i < count; ++i)
    buf[i] = tmp[i];
  std::cout << "Buff : " << buf << std::endl;
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
