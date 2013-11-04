#ifndef AMONITORABLE_H_
# define AMONITORABLE_H_

#include "abs_sockets.h"

#if defined(WIN32)
#include <winsock2.h>
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
# define SOCKET int
#endif

namespace net
{

  class  ABS_SOCKET_API AMonitorable
  {
  public:
    AMonitorable(bool read = true, bool write = true);
    virtual ~AMonitorable();

  private:
    AMonitorable(AMonitorable const&);
    AMonitorable& operator=(AMonitorable const&);

  public:
    void	monitor(bool read = true, bool write = true);
    bool	monitorRead() const;
    bool	monitorWrite() const;

  public:
    void		read(bool);
    bool		read() const;
    void		write(bool);
    bool		write() const;
    virtual SOCKET	getSocket() const = 0;

  protected:
    bool	_monitorRead;
    bool	_monitorWrite;
    bool	_readSet;
    bool	_writeSet;
  };

}

#endif /* AMONITORABLE_HH_ */
