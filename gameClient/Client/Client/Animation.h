#ifndef ANIMATION_
# define	ANIMATION_

# include	<SFML\Graphics.hpp>

# include	"Timer.h"

enum AnimationType
{
	Left = 0,
	Right,
	Up,
	Down,
	Fire,
	Destroy,
	Nothing,
};

class Animation
{
private:
	std::vector<sf::IntRect>	m_frames;
	sf::Texture*				m_texture;

public:
	void addFrame(sf::IntRect rect);
	std::size_t getSize() const;
	const sf::IntRect& getFrame(std::size_t n) const;

public:
	Animation(const sf::Texture& texture) {}
	~Animation() {}

private:
	Animation(const Animation &);
	Animation				operator=(const Animation &);
};


#endif // !ANIMATION_
