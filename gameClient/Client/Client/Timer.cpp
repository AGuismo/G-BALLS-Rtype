#include		"Timer.h"

bool			Timer::isEnded()
{
	return ((_tClock.getElapsedTime() > *_tTime) ? true : false);
}

void			Timer::restart()
{
	_tClock.restart();
}

void			Timer::reset(sf::Time *nTime)
{
	_tTime = nTime;
	_tClock.restart();
}


void			reset(sf::Time *nTime);

Timer::Timer(sf::Time *tTime)
{
	_tTime = tTime;
}