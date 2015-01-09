#pragma once

class Time
{
public:
	typedef unsigned long long time_type;

	Time();
	~Time();

	Time(const Time &src);
	Time	&operator=(const Time &src);

	static const Time	milliseconds(unsigned long int milli);
	static const Time	microseconds(unsigned long int micro);
	static const Time	seconds(float seconds);

	time_type			asMicroseconds() const;
	unsigned long int	asMillieconds() const;
	float				asSeconds() const;

private:
	time_type	_time;
};