#ifndef LAYERMANAGER_
# define	LAYERMANAGER_

#include	<map>

# include	"EnumObject.h"
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
	typedef std::map<ObjType, Layer *> layer_type;
	layer_type						_layers;

public:
	bool							addLayer(ObjType layer, sf::Vector2f *lReset, sf::Vector2f *lLim, float lInc, bool lEn);
	bool							enableLayer(ObjType layer);
	bool							stopLayer(ObjType layer);
	bool							resetLayer(ObjType layer);

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
