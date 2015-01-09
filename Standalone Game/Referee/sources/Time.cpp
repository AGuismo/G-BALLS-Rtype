#include	"Time.hh"

Time::Time()
{

}

Time::~Time()
{

}

Time::Time(const Time &src):
_time(src._time)
{

}

Time	&Time::operator=(const Time &src)
{
	if (&src != this)
	{
		_time = src._time;
	}
	return (*this);
}

Time::time_type	Time::asMicroseconds() const
{
	return (_time);
}

unsigned long int	Time::asMillieconds() const
{
	return (_time / 1000L);
}

float		Time::asSeconds() const
{
	return ((float)_time / 1000000.f);
}

const Time	Time::milliseconds(unsigned long int milli)
{
	Time	t;

	t._time = milli * 1000L;
	return (t);
}

const Time	Time::microseconds(unsigned long int micro)
{
	Time	t;

	t._time = micro;
	return (t);
}

const Time	Time::seconds(float seconds)
{
	Time	t;

	t._time = seconds * 1000000L;
	return (t);
}
