#include "ClientAccepted.h"
#include <exception>

using namespace net;

#if defined(WIN32)
ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr)
{
  WinInit::GetInstance();
  _sock = sock;
  _addr = addr;
}

ClientAccepted::ClientAccepted()
{
  WinInit::GetInstance();
}

ClientAccepted::~ClientAccepted()
{
}

void ClientAccepted::recv()
{
  DWORD						count, flags = MSG_OOB;
  WSABUF						wbuff;
  std::vector<cBuffer::Byte>	tmp;
  int  size = sizeof(_addr);

  WSARecvFrom(_sock, &wbuff, 1, &count, &flags, reinterpret_cast<sockaddr *>(&_addr), &size, NULL, NULL);
  for (int i = 0; i < size ; i++)
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
      throw std::exception("Recv Failure");
    }
  if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
  _write.read(tmp, size);
  count = _write.look(tmp, 512);
  if (!count)
    _type = READ;
}

void ClientAccepted::close()
{
  if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw std::exception("Close Failure");
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

ClientAccepted::ClientAccepted(SOCKET sock, struct sockaddr_in addr)
{
  _sock = sock;
  _addr = addr;
}

ClientAccepted::ClientAccepted()
{
}

ClientAccepted::~ClientAccepted()
{
}

void ClientAccepted::recv()
{
  int						count = 512, flags = MSG_OOB;
  char						buf[512];
  std::vector<cBuffer::Byte>	tmp;
  socklen_t  size = sizeof(_addr);

  recvfrom(_sock, buf, count, flags, reinterpret_cast<sockaddr *>(&_addr), &size);
  for (socklen_t i = 0; i < size ; i++)
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
  n = sendto(_sock, buf, size, MSG_OOB, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  if (n == -1)
    {
      _state = STATEERROR;
      throw std::exception();
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
  if (::close(_sock) == -1)
    {
      _state = STATEERROR;
      throw std::exception();
    }
  _state = DISCONNECTED;
  _sock = 0;
}

SOCKET		ClientAccepted::getSocket()const
{
  return _sock;
}

#endif

void ClientAccepted::readFromBuffer(std::string &str)
{
  std::vector<cBuffer::Byte>		tmp;
  char	buf[512];
  int count;

  count = _read.read(tmp, 512);
  for (int i = 0; i < count ; i++)
    buf[i] = tmp[i];
  str = buf;
  if (_type != WRITE && _type != BOTH)
    _type = READ;
  else
    _type = BOTH;
}

void ClientAccepted::writeIntoBuffer(const std::string &str)
{
  std::vector<cBuffer::Byte>		tmp;

  for (unsigned int i = 0; i < str.length() ; i++)
    tmp.insert(tmp.end(), str.c_str()[i]);
  _read.write(tmp, str.length());
  if (_type != READ && _type != BOTH)
    _type = WRITE;
  else
    _type = BOTH;
}

cBuffer::size_type ClientAccepted::lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
  return _read.look(buf, count);
}

cBuffer::size_type ClientAccepted::lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
  return _write.look(buf, count);
}
