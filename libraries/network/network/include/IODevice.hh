#ifndef IODEVICE_H_
# define IODEVICE_H_

# include	"abs_sockets.h"

namespace	net
{
  class ABS_SOCKET_API IODevice
  {
  public:
    virtual ~IODevice() {}

  public:
    virtual int		readData(char *, int) = 0;
    virtual int		writeData(const char *, int) = 0;
    virtual void	close() = 0;

  public:
    virtual bool	isOpen() const = 0;
    virtual bool	isClosed() const = 0;
    virtual bool	isDisconnected() const = 0;
  };
}

#endif /* IODEVICE_H_ */
