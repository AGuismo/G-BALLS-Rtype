#ifndef CLOCK_H_
# define CLOCK_H_

typedef long long	clock_time;

class	gameClock
{
public:
	gameClock();
	~gameClock();

	void		start();
	void		update();

	clock_time	getElapsedTime() const {return _elapsedTime;};
	clock_time	getTotalElapsedTime() const { return _totalElapsedTime;};

private:

# if defined(WIN32)
  LARGE_INTEGER		_last;
  LARGE_INTEGER		_procFreq;
# elif defined(linux)
  struct timeval	_last;
#endif

  clock_time		_elapsedTime;
  clock_time		_totalElapsedTime;

  static const long CLOCK_PREC = 1000000;
};

#endif /* CLOCK_H_ */
