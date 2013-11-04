#pragma once

#include <exception>
#include "AMonitorable.h"
#include "cBuffer.h"
#include "abs_sockets.h"
#include "state.h"
#if defined(WIN32)
# include <WinSock2.h>
# include "WinInit.h"
# pragma comment(lib, "WS2_32.lib")
#elif defined(linux)
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
#else
# error "Unsupported Operating System"
#endif

namespace net
{
  class ABS_SOCKET_API ClientAccepted: public AMonitorable
  {
  public:
    ClientAccepted();
    ClientAccepted(SOCKET sock, struct sockaddr_in addr);
    ~ClientAccepted();

    int			recv();
    int			send();
    void		close();
    cBuffer::size_type	readFromBuffer(std::vector<cBuffer::Byte> &, cBuffer::size_type count);
    cBuffer::size_type	writeIntoBuffer(const std::vector<cBuffer::Byte> &, cBuffer::size_type count);
    cBuffer::size_type	lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
    cBuffer::size_type	lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
    struct sockaddr_in	_addr;

  public:
    bool		isOpen() const;
    bool		isClosed() const;
    bool		isDisconnected() const;

  protected:
    SOCKET		getSocket()const;

  protected:
    SOCKET		_sock;
    State		_state;
    cBuffer		_read;
    cBuffer		_write;
  };
}
