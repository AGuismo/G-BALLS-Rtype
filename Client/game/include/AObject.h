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
	Action					_action;

protected:
	bool					_act;
	bool					_alive;

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
	Timer					_timerMvt;
	float					_mvtTime;

protected:
	float					_vLag;
	float					_decX;
	float					_decY;

public:
	void					findAnimation(void);

public:
	virtual void			draw(void) = 0;
	virtual void			update(LookDirection lDir, int updatedPos) = 0;
	virtual void			onDestruction(Game &game) = 0;
public:
	const sf::Vector2f		&getVectorNextPos(void);
	const sf::Vector2f		&getVectorCurPos(void);
	int						getCaseNextPos(void);
	int						getCaseCurPos(void);

public:
	ObjType					getObjType(void);
	int						getObjId(void);

public:
	bool					isAlive(void);

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
