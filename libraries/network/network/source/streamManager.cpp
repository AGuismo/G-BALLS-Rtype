#include "streamManager.h"

using namespace net;

streamManager::streamManager()
{
	_timeout.tv_sec = 0;
	_timeout.tv_usec = 0;
	FD_ZERO(&_readMonitor);
	FD_ZERO(&_writeMonitor);
}

streamManager::~streamManager()
{

}


void streamManager::setOption(Opt option, const struct timeval &timeout)
{
	switch (option)
	{
	case NONBLOCK:
		_optNonBlocking = false;
		break;
	case TIMEOUT:
		_optNonBlocking = true;
		_optTimeout = true;
		_timeout = timeout;
      break;
    default: break;
	}	
}

void streamManager::unsetOption(Opt option)
{
	switch (option)
    {
    case NONBLOCK:
      _optNonBlocking = true;
      break;
    case TIMEOUT:
      _optNonBlocking = false;
	  _optTimeout = false;
      break;
    default: break;
    }
}

bool streamManager::isOptionSet(Opt option) const
{
	if (option == NONBLOCK)
		return (_optNonBlocking);
	else if (option == TIMEOUT)
		return (_optTimeout);
	return (false);
}

void streamManager::clear()
{
	FD_ZERO(&_readMonitor);
	FD_ZERO(&_writeMonitor);
	_monitors.clear();
	_isTimeout = false;

}

void streamManager::run()
{
	std::vector<AMonitorable *>::iterator	it;

	FD_ZERO(&_readMonitor);
	FD_ZERO(&_writeMonitor);
	for (it = _monitors.begin(); it != _monitors.end(); it++)
    {
		if ((*it)->getSocket() > _maxFd)
			_maxFd = (*it)->getSocket();
		if ((*it)->isSet(AMonitorable::READ))
			FD_SET((*it)->getSocket(), &_readMonitor);
		if ((*it)->isSet(AMonitorable::WRITE))
			FD_SET((*it)->getSocket(), &_writeMonitor);
    }

	if (_optTimeout || _optNonBlocking)
	{
      struct timeval	tv = _timeout;
      int		ret;

      _isTimeout = false;
      if (_optNonBlocking)
		tv.tv_sec = tv.tv_usec = 0;
      ret = select(_maxFd + 1, &_readMonitor, &_writeMonitor, 0, &tv);
      if (ret == -1)
		  throw std::exception("Select Timeout");
      if (ret == 0)
		{
		_isTimeout = true;
		return ;
		}
    }
  else
    {
      if (select(_maxFd + 1, &_readMonitor, &_writeMonitor, 0, 0) == -1)
		{
//		strerror(errno);
		throw std::exception("Select");
		}
    }
  for (it = _monitors.begin(); it != _monitors.end(); it++)
    {
      if (FD_ISSET((*it)->getSocket(), &_readMonitor))
		(*it)->read(true);
      else
		(*it)->read(false);
      if (FD_ISSET((*it)->getSocket(), &_writeMonitor))
		(*it)->write(true);
	  else
		(*it)->write(false);
    }
}

bool streamManager::isTimeout() const
{
	  return (_isTimeout);
}

const struct timeval &streamManager::getTimeval() const
{
  return (_timeout);
}
