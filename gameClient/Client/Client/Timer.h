#ifndef TIMER_
# define	TIMER_

# include	<SFML/Graphics.hpp>

class Timer
{
private:
	sf::Clock		_tClock;
	sf::Time		*_tTime;

public:
	bool			isEnded();
	void			restart();
	void			reset(sf::Time *nTime);

public:
	Timer(sf::Time *tTime);
	Timer() {}
};


#endif // !TIMER_
