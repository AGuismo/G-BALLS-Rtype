#ifndef ANIMATION_
# define	ANIMATION_

# include	<SFML\Graphics.hpp>
# include	"Timer.h"

class Animation
{
private:
	typedef std::vector<sf::IntRect>	frames_type;

private:
	frames_type							_frames;
	Timer								*_aTimer;

private:
	std::size_t							_curFrame;

public:
	void								addFrame(sf::IntRect rect);
	const sf::IntRect&					getFrame(void);

public:
	Animation(sf::Time *aTime) : _aTimer(new Timer(aTime)) {}
	~Animation() {}

private:
	Animation(const Animation &);
	Animation				operator=(const Animation &);
};


#endif // !ANIMATION_
