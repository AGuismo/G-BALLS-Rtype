#include	"ClientAccepted.h"
#include	"NetException.h"
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

void ClientAccepted::recv()
{
  DWORD				count, flags = MSG_OOB;
  WSABUF			wbuff;
  std::vector<cBuffer::Byte>	tmp;
  int				size = sizeof(_addr);

  WSARecvFrom(_sock, &wbuff, 1, &count, &flags, reinterpret_cast<sockaddr *>(&_addr), &size, NULL, NULL);
  for (DWORD i = 0; i < count ; i++)
    tmp.insert(tmp.end(), wbuff.buf[i]);
  _read.write(tmp, size);
}

void ClientAccepted::send()
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
      throw net::Exception("Recv Failure");
    }
  if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  _write.read(tmp, size);
  count = _write.look(tmp, 512);
}

void ClientAccepted::close()
{
  if (_state == DISCONNECTED)
    return ;
  if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure");
    }
  _state = DISCONNECTED;
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

ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr)
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

void ClientAccepted::recv()
{
  int				count = 512;
  char				buf[512];
  std::vector<cBuffer::Byte>	tmp;
  socklen_t			size = sizeof(_addr);
  ssize_t			readSize;

  readSize = recvfrom(_sock, buf, count, 0, reinterpret_cast<sockaddr *>(&_addr), &size);
  if (readSize == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Recvfrom Failure" + std::string(strerror(errno)));
    }
  if (readSize == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  for (socklen_t i = 0; i < readSize ; i++)
    tmp.insert(tmp.end(), buf[i]);
  _read.write(tmp, size);
}

void ClientAccepted::send()
{
  ssize_t				count, n;
  std::vector<cBuffer::Byte>		tmp;
  char	buf[512];
  size_t		size;
  int i;

  count = _write.look(tmp, 512);
  for (i = 0; i < count ; i++)
    buf[i] = tmp[i];
  size = i;
  n = sendto(_sock, buf, size, 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  if (n == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Sendto Failure" + std::string(strerror(errno)));
    }
  if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  _write.read(tmp, size);
}

void ClientAccepted::close()
{
  if (_state == DISCONNECTED)
    return ;
  if (::close(_sock) == -1)
    {
      _state = STATEERROR;
      throw net::Exception("Close Failure" + std::string(strerror(errno)));
    }
  _state = DISCONNECTED;
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

bool			ClientAccepted::isClosed() const
{
  return (_state == DISCONNECTED);
}

cBuffer::size_type	ClientAccepted::readFromBuffer(std::vector<cBuffer::Byte> &buf,
						       cBuffer::size_type count)
{
  return (_read.read(buf, count));
}

cBuffer::size_type	ClientAccepted::writeIntoBuffer(const std::vector<cBuffer::Byte> &buf,
						   cBuffer::size_type count)
{
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
