#ifndef LAYERMANAGER_
# define	LAYERMANAGER_

#include	<deque>

# include	"EnumObject.h"
# include	"EnumLayer.h"
# include	"Layer.h"

class TextureManager;

namespace sf
{
	class RenderWindow;
}
class								LayerManager
{
private:
	sf::RenderWindow				*_gameWindow;
	TextureManager					*_textureManager;

private:
	typedef std::deque<Layer *> layers_type;
	layers_type						_layers;

public:
	bool							addLayer(ObjType objType, LayerType lType, sf::Vector2f *lReset, sf::Vector2f *lLim, sf::Vector2f *lInc, bool lEn);
	bool							enableLayer(LayerType layer);
	bool							stopLayer(LayerType layer);
	bool							resetLayer(LayerType layer);

public:
	void							draw(void);
	void							update(void);

public:
	LayerManager(sf::RenderWindow *gameWindow, TextureManager *TextureManager);
	~LayerManager() {}

private:
	LayerManager(const LayerManager &);
	LayerManager					operator=(const LayerManager &);
};


#endif // !LAYERMANAGER_
