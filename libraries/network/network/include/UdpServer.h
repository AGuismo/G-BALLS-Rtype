#pragma once

#if defined(WIN32)
# include	<Winsock2.h>
# include	"WinInit.h"
#elif defined(linux)
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<arpa/inet.h>
#endif
# include	"ClientAccepted.h"
# include	"AMonitorable.h"
# include	"abs_sockets.h"
# include	"cBuffer.h"
# include	"IODevice.hh"

namespace net
{
  class ABS_SOCKET_API UdpServer : public AMonitorable, public IODevice
  {
  public:
    static const int	NB_CLIENTS = 10;

  public:
    UdpServer(void);
    ~UdpServer(void);

  public:
    void initialize(int port, int nbClients = NB_CLIENTS);
    void recv();

  private:
    int		readData(char *, int);
    int		writeData(const char *, int);

  public:
    void	send();
    void	close();

  public:
    bool	isOpen() const;
    bool	isClosed() const;
    bool	isDisconnected() const;

  public:
    cBuffer::size_type readFromBuffer(std::vector<cBuffer::Byte> &, cBuffer::size_type count);
    cBuffer::size_type writeIntoBuffer(const std::vector<cBuffer::Byte> &, cBuffer::size_type count);
    cBuffer::size_type lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
    cBuffer::size_type lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);

    void	setClientAddr(struct sockaddr_in s);
    struct sockaddr_in		getClientAddr() const;

  private:
    SOCKET	getSocket() const;

  private:
    SOCKET		_sock;
    State		_state;
    cBuffer		_read;
    cBuffer		_write;
    struct sockaddr_in	_addr;
    struct sockaddr_in	_clientAddr;
  };
}
