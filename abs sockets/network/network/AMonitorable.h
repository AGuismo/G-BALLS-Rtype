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
    enum	Type
      {
		READ,
		WRITE,
		BOTH,
		NONE
      };


  public:
    AMonitorable();
    AMonitorable(Type monitorType);
    virtual ~AMonitorable();

  public:
    // AMonitorable(AMonitorable const&);
    // AMonitorable& operator=(AMonitorable const&);

  public:
    Type	getType() const;
    bool	isSet(Type) const;

  public:
    void	read(bool);
    bool	read() const;
    void	write(bool);
    bool	write() const;
	virtual	SOCKET getSocket()const = 0;

  protected:
    Type	_type;
    bool	_readSet;
    bool	_writeSet;
  };

}

#endif /* AMONITORABLE_HH_ */