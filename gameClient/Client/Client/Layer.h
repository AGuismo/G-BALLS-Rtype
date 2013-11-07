#ifndef LAYER_
#define	LAYER_

# include	<SFML/Graphics.hpp>

class Layer
{
private:
	sf::Texture					*_lTexture;
	sf::Sprite					_lSprite;

private:
	sf::Vector2f				*_lCurPos;
	sf::Vector2f				*_lLimPos;
	float						_layerIncrement;

public:
	void						draw(void);
	void						update(void);
	void						enable(bool en);

public:
	Layer(sf::Texture *lText, sf::Vector2f *lLim, float lInc, bool lEn);
	~Layer() {}
};

#endif // !LAYER_
