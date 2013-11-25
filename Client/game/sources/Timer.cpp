#include		"Timer.h"

bool			Timer::isEnded()
{
	return ((_tClock.getElapsedTime() > _tTime) ? true : false);
}

void			Timer::restart()
{
	_tClock.restart();
}

void			Timer::reset(const sf::Time &nTime)
{
  _tTime = nTime;
  _tClock.restart();
}


Timer::Timer(const sf::Time &tTime) :
  _tTime(tTime)
{
}

Timer::Timer(const Timer &src):
  _tClock(src._tClock), _tTime(src._tTime)
{

}

Timer	&Timer::operator=(const Timer &src)
{
  if (&src != this)
    {
      _tClock = src._tClock;
      _tTime = src._tTime;
    }
  return (*this);
}
