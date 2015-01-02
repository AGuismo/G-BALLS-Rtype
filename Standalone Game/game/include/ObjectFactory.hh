#ifndef OBJECT_FACTORY
# define	OBJECT_FACTORY

# include	<map>
# include	"RequestCode.hh"
# include	"Entity.hh"

class	Position;
class	ObjectMover;
class	Animation;

namespace	game
{
  class	TextureManager;
}

class					ObjectFactory
{
private:
	typedef std::map<unsigned short, std::string>	texture_code_map_type;

private:
	game::TextureManager	*_textureManager;
	texture_code_map_type	_codes;

public:
	ObjectMover			*createObject(const Entity::type &type, unsigned short id, const Position &pos);
	void				init(game::TextureManager *);

public:
	static ObjectFactory		&getInstance(void);

private:
	const Animation				getAnimation(const Entity::type &t) const;

	ObjectFactory();
	~ObjectFactory();

private:
	ObjectFactory(const ObjectFactory &);
	ObjectFactory			operator=(const ObjectFactory &);
};

#endif // !OBJECT_FACTORY
