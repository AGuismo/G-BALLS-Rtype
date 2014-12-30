#ifndef LAYER_
#define	LAYER_

# include	<SFML/Graphics.hpp>
# include	"Timer.h"
# include	"EnumObject.h"
# include	<algorithm>
# include	<functional>

//# include	"EnumLayer.h"

class Layer
{
private:
	int							_id;
	sf::Texture					*_lTexture;
	sf::Sprite					_lSprite;

private:
	sf::RenderWindow			*_gameWindow;

private:
	sf::Vector2f				_lCurPos;
	sf::Vector2f				_lInitPos;
	sf::Vector2f				_lResetPos;
	sf::Vector2f				_lLimPos;
	sf::Vector2f				_lIncrement;
	bool						_lEnabled;

private:
	Timer						*_lTime;

public:
	void						draw(void);
	void						update(void);
	void						enable(void);
	void						disable(void);

public:
  Layer(int id, sf::Texture *lText, const sf::Vector2f &lInit,
	const sf::Vector2f &lReset, const sf::Vector2f &lLim,
	const sf::Vector2f &lInc, Timer *lT, sf::RenderWindow *gWindow, bool lEn);
  ~Layer() {}

public:
	struct predicate : std::unary_function<Layer *, bool>
	{
		predicate(const int id) : _id(id) {}
		bool	operator()(const Layer *layer) const
		{
			return (layer->_id == _id);
		};
		const int	_id;
	};

private:
	Layer(const Layer &);
	Layer						operator=(const Layer &);
};

#endif // !LAYER_
