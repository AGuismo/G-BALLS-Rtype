#ifndef LAYER_
#define	LAYER_

# include	<SFML/Graphics.hpp>
# include	"EnumObject.h"

class Layer
{
private:
	sf::Texture					*_lTexture;
	sf::Sprite					_lSprite;

private:
	sf::Vector2f				*_lCurPos;
	sf::Vector2f				*_lResetPos;
	sf::Vector2f				*_lLimPos;
	float						_layerIncrement;

private:
	sf::RenderWindow			*_gameWindow;

public:
	void						draw(void);
	void						update(void);
	void						enable(bool en);

public:
	Layer(ObjType type, sf::Texture *lText, sf::Vector2f *lReset, sf::Vector2f *lLim, sf::RenderWindow *gWindow, float lInc, bool lEn);
	~Layer() {}

private:
	Layer(const Layer &);
	Layer						operator=(const Layer &);
};

#endif // !LAYER_
