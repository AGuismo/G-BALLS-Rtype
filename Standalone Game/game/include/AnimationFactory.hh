#ifndef ANIMATION_FACTORY
# define	ANIMATION_FACTORY

# include	<map>
# include	"RequestCode.hh"
# include	"Entity.hh"

class	Position;
class	Animation;

namespace	game
{
  class	TextureManager;
}

class					AnimationFactory
{
private:
	typedef std::map<unsigned short, std::string>	texture_code_map_type;

private:
	game::TextureManager	*_textureManager;
	texture_code_map_type	_codes;

public:
	Animation			createAnimation(const Entity::type &type);
	void				init(game::TextureManager *);

public:
	static AnimationFactory		&getInstance(void);

private:
	const Animation				getAnimation(const Entity::type &t) const;

	AnimationFactory();
	~AnimationFactory();

private:
	AnimationFactory(const AnimationFactory &);
	AnimationFactory			operator=(const AnimationFactory &);
};

#endif // !ANIMATION_FACTORY
