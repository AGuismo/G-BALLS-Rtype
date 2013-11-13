#ifndef AOBJECT
# define AOBJECT

# include	<SFML/Graphics.hpp>
# include	<algorithm>
# include	"IObject.h"
# include	"Timer.h"

class AObject : public IObject
{
protected:
	int					_id;
	ObjType				_type;
	LookDirection		_ld;
	sf::Texture			*_texture;
	sf::Sprite			_image;
	sf::Vector2f		*_vCurPos;
	sf::Vector2f		*_vNextPos;
	Timer				*_timer;
	Timer				*_timerMvt;
	int					_cCurPos;
	int					_cNextPos;
	bool				_act;
	float				_vLag;
	float				_mvtTime;
	sf::Vector2f		_gPos;
	sf::RenderWindow	*_gameWindow;

public:
	virtual void			draw(void) = 0;
	virtual void			update(Action act, int updatedPos) = 0;
	virtual sf::Vector2f	*getVectorNextPos(void) = 0;
	virtual sf::Vector2f	*getVectorCurPos(void) = 0;
	virtual int				getCaseNextPos(void) = 0;
	virtual int				getCaseCurPos(void) = 0;

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