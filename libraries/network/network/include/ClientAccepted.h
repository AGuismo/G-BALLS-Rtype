#pragma once

#if defined(WIN32)
# include	<WinSock2.h>
# include	"WinInit.h"
# pragma comment(lib, "WS2_32.lib")
#elif defined(linux)
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<arpa/inet.h>
#else
# error "Unsupported Operating System"
#endif
# include	<exception>
# include	"AMonitorable.h"
# include	"cBuffer.h"
# include	"state.h"
# include	"IODevice.hh"

namespace net
{
  class ClientAccepted: public AMonitorable, public IODevice
  {
  public:
    ClientAccepted();
    ClientAccepted(SOCKET sock, struct sockaddr_in addr);
    ~ClientAccepted();

  protected:
    int			readData(char *, int);
    int			writeData(const char *, int);

  public:
    int			recv();
    int			send();
    void		close();
    cBuffer::size_type	readFromBuffer(cBuffer::stor_type &, cBuffer::size_type count);
    cBuffer::size_type	writeIntoBuffer(const cBuffer::stor_type &, cBuffer::size_type count);
    cBuffer::size_type	lookRead(cBuffer::stor_type &buf, cBuffer::size_type count);
    cBuffer::size_type	lookWrite(cBuffer::stor_type &buf, cBuffer::size_type count);
    struct sockaddr_in	_addr;

  public:
    bool		isOpen() const;
    bool		isClosed() const;
    bool		isDisconnected() const;

  protected:
    SOCKET		getSocket() const;

  protected:
    SOCKET		_sock;
    State		_state;
    cBuffer		_read;
    cBuffer		_write;

    friend class	UdpServer;
    friend class	TcpServer;
  };
}
