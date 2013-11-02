#include	"AMonitorable.h"

using namespace net;

AMonitorable::AMonitorable(bool read, bool write) :
  _monitorRead(read), _monitorWrite(write), _readSet(false), _writeSet(false)
{

}

AMonitorable::~AMonitorable()
{

}

bool		AMonitorable::monitorRead() const
{
  return (_monitorRead);
}

bool		AMonitorable::monitorWrite() const
{
  return (_monitorWrite);
}

void			AMonitorable::monitor(bool read, bool write)
{
  _monitorRead = read;
  _monitorWrite = write;
}

void			AMonitorable::read(bool read)
{
  _readSet = read;
}

bool			AMonitorable::read() const
{
  return (_readSet);
}

void			AMonitorable::write(bool write)
{
  _writeSet = write;
}

bool			AMonitorable::write() const
{
  return (_writeSet);
}
