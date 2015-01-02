#ifndef TIMER_
# define	TIMER_

# include	<SFML/Graphics.hpp>

class Timer
{
private:
	sf::Clock		_tClock;
	sf::Time		_tTime;

public:
	bool			isEnded();
	void			restart();
	void			reset(const sf::Time &nTime);

public:
	Timer(const sf::Time &);
	Timer() {}

public:
  Timer(const Timer &);
  Timer	&operator=(const Timer &);
};


#endif // !TIMER_
