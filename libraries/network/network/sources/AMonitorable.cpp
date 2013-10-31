#include	"AMonitorable.h"

using namespace net;

AMonitorable::AMonitorable() :
  _type(NONE), _readSet(false), _writeSet(false)
{

}

AMonitorable::AMonitorable(AMonitorable::Type type) :
  _type(type), _readSet(false), _writeSet(false)
{
}

AMonitorable::~AMonitorable()
{

}

AMonitorable::Type	AMonitorable::getType() const
{
  return (_type);
}


bool			AMonitorable::isSet(AMonitorable::Type type) const
{
  if ((type == READ || type == BOTH) && (_type == READ || _type == BOTH))
    return (true);
  if ((type == WRITE || type == BOTH) && (_type == WRITE || _type == BOTH))
    return (true);
  return (false);
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
