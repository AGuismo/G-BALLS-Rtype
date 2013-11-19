#include "streamManager.h"
#include "NetException.h"
#include <algorithm>
#if defined(linux)
# include	<errno.h>
# include	<cstring>
#endif
#include	<iostream>

using namespace net;

streamManager::streamManager():
  _isTimeout(false), _optTimeout(false), _optNonBlocking(false), _maxFd(0)
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
      _optNonBlocking = true;
      break;
    case TIMEOUT:
      _optNonBlocking = false;
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
      _optNonBlocking = false;
      break;
    case TIMEOUT:
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

bool	streamManager::timeoutMode()
{
  struct timeval	tv = _timeout;
  int		ret;

  _isTimeout = false;
  if (_optNonBlocking)
    tv.tv_sec = tv.tv_usec = 0;
  ret = select(_maxFd + 1, &_readMonitor, &_writeMonitor, 0, &tv);
  if (ret == -1)
    {
#if defined(WIN32)
      throw net::Exception("Select Failure: ");
#elif defined(linux)
      throw net::Exception("Select Failure: " + std::string(strerror(errno)));
#endif
    }
  if (ret == 0)
    {
      _isTimeout = true;
      return (false);
    }
  return (true);
}

void streamManager::run()
{
  std::vector<AMonitorable *>::iterator	it;

  FD_ZERO(&_readMonitor);
  FD_ZERO(&_writeMonitor);
  for (it = _monitors.begin(); it != _monitors.end(); ++it)
    {
      if ((*it)->getSocket() > _maxFd)
	_maxFd = (*it)->getSocket();
      if ((*it)->monitorRead())
	FD_SET((*it)->getSocket(), &_readMonitor);
      if ((*it)->monitorWrite())
	FD_SET((*it)->getSocket(), &_writeMonitor);
    }
  if (_optTimeout || _optNonBlocking)
    {
      if (!timeoutMode())
	return ;
    }
  else
    {
      if (select(_maxFd + 1, &_readMonitor, &_writeMonitor, 0, 0) == -1)
	{
#if defined(WIN32)
	  throw net::Exception("Select Failure: ");
#elif defined(linux)
	  throw net::Exception("Select Failure: " + std::string(strerror(errno)));
#endif
	}
    }
  for (it = _monitors.begin(); it != _monitors.end(); ++it)
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

void	streamManager::setMonitor(AMonitorable &toMonitor)
{
  _monitors.push_back(&toMonitor);
}

void	streamManager::unsetMonitor(AMonitorable &toUnmonitor)
{
  std::vector<AMonitorable *>::iterator	pos = std::find(_monitors.begin(),
							_monitors.end(),
							&toUnmonitor);

  if (pos != _monitors.end())
    _monitors.erase(pos);
#if defined(DEBUG)
  else
    throw net::Exception("The network don't exist in this streamMonitor");
#endif
}
