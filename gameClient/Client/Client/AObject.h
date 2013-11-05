#ifndef AOBJECT
# define AOBJECT

# include	<SFML/Graphics.hpp>
# include	<algorithm>
# include	"IObject.h"

class AObject : public IObject
{
protected:
	int					_id;
	ObjType				_type;
	sf::Texture			*_texture;
	sf::Sprite			_image;
	int					_pos;
	sf::RenderWindow	*_gameWindow;

public:
	virtual void		draw(void) = 0;
	virtual void		update(int newPos, Action act) = 0;

public:
	virtual	~AObject() {}

public:
	struct predicate : std::unary_function<AObject, bool>
	{
		predicate(const int id) : _id(id) {}
		bool	operator()(const AObject &obj) const { return (obj._id == _id); };
		const int	_id;
	};
};

#endif // !IOBJECT