#ifndef ANIMATION_
# define	ANIMATION_

# include	<vector>
# include	<map>
# include	<string>
# include	<SFML/Graphics.hpp>
# include	"Timer.hh"
# include	"Entity.hh"

class Animation
{
public:
	static const std::string	ACT_DEFAULT;
	static const std::string	ACT_UP;
	static const std::string	ACT_DOWN;

	static const float			ANIM_FRAME_DURATION;

private:
	typedef std::vector<sf::Texture *>			frames_type;
	typedef std::map<std::string, frames_type>	action_type;

private:
	Entity::type		_type;
	action_type			_animations;
	Timer				_aTimer;

	std::string			_curAction;
	std::size_t			_curFrame;

public:
	void				addFrame(const std::string &action, sf::Texture *textureFrame);
	const sf::Texture&	getFrame(const std::string &action = ACT_DEFAULT);

public:
	Animation();
	Animation(const Entity::type &, float frameDuration = ANIM_FRAME_DURATION);
	~Animation() {}

public:
	Animation(const Animation &);
	Animation				&operator=(const Animation &);
};


#endif // !ANIMATION_
