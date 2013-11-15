#ifndef AOBJECT
# define AOBJECT

# include	<SFML/Graphics.hpp>
# include	<algorithm>
# include	"game.h"
# include	"IObject.h"


class AObject : public IObject
{
protected:
	int						_id;
	ObjType					_type;
	LookDirection			_ld;

protected:
	bool					_act;

protected:
	sf::Texture				*_texture;
	sf::Sprite				_image;
	sf::RenderWindow		*_gameWindow;

protected:
	int						_cCurPos;
	int						_cNextPos;
	sf::Vector2f			_vCurPos;
	sf::Vector2f			_vNextPos;

protected:
	Timer					*_timerMvt;
	float					_mvtTime;

protected:
	float					_vLag;
	float					_decX;
	float					_decY;

public:
	Action					findDirection(int newPos, int oldPos)

public:
	virtual void			draw(void) = 0;
	virtual void			update(Action act, LookDirection lDir, int updatedPos) = 0;

public:
	const sf::Vector2f		&getVectorNextPos(void);
	const sf::Vector2f		&getVectorCurPos(void);
	int						getCaseNextPos(void);
	int						getCaseCurPos(void);

public:
	virtual	~AObject() {}

public:
	struct predicate : std::unary_function<AObject *, bool>
	{
		predicate(const int id) : _id(id) {}
		bool	operator()(const AObject *obj) const
		{
			return (obj->_id == _id);
		};
		const int	_id;
	};
};

#endif // !IOBJECT