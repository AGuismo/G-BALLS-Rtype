#ifndef LAYER_
#define	LAYER_

# include	<SFML/Graphics.hpp>
# include	"Timer.h"
# include	"EnumObject.h"

class Layer
{
private:
	LayerType					_lType;
	sf::Texture					*_lTexture;
	sf::Sprite					_lSprite;

private:
	sf::RenderWindow			*_gameWindow;

private:
	sf::Vector2f				*_lCurPos;
	sf::Vector2f				*_lResetPos;
	sf::Vector2f				*_lLimPos;
	sf::Vector2f				*_lIncrement;
	bool						_lEnabled;

private:
	Timer						*_lTime;

public:
	void						draw(void);
	void						update(void);
	void						enable(void);
	void						disable(void);

public:
	Layer(LayerType type, sf::Texture *lText, sf::Vector2f *lReset, sf::Vector2f *lLim, sf::Vector2f *lInc, sf::RenderWindow *gWindow, bool lEn);
	~Layer() {}

private:
	Layer(const Layer &);
	Layer						operator=(const Layer &);
};

#endif // !LAYER_
