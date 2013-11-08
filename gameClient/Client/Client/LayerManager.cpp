#include		"LayerManager.h"
#include		"TextureManager.h"
#include		"Timer.h"

#include		<algorithm>

bool							LayerManager::addLayer(ObjType objType, LayerType lType, sf::Vector2f *lInit, sf::Vector2f *lReset, sf::Vector2f *lLim, sf::Vector2f *lInc, Timer *lTimer, bool lEn)
{
	Layer						*newL;
	sf::Texture					*text;

	if ((text = _textureManager->getTexture(objType)) != NULL)
	{
		newL = new Layer(lType, text, lInit, lReset, lLim, lInc, lTimer, _gameWindow, lEn);
		_layers.push_back(newL);
		return true;
	}
	return false;
}

Layer							*LayerManager::findLayer(int lId)
{
	layers_type::iterator it = std::find_if(_layers.begin(), _layers.end(), Layer::predicate(lId));
	if (it != _layers.end())
	{
		return *it;
	}
	return NULL;
}

bool							LayerManager::enableLayer(LayerType layer)
{
	Layer						*lTmp;

	if ((lTmp = findLayer(layer)) != NULL)
	{
		lTmp->enable();
		return true;
	}
	return false;
}

bool							LayerManager::stopLayer(LayerType layer)
{
	Layer						*lTmp;

	if ((lTmp = findLayer(layer)) != NULL)
	{
		lTmp->disable();
		return true;
	}
	return false;
}


void							LayerManager::draw(void)
{
	for (layers_type::iterator it = _layers.begin(); it != _layers.end(); ++it)
		(*it)->draw();
}


void							LayerManager::update(void)
{
	for (layers_type::iterator it = _layers.begin(); it != _layers.end(); ++it)
		(*it)->update();
}

void							LayerManager::upDraw(void)
{
	for (layers_type::iterator it = _layers.begin(); it != _layers.end(); ++it)
	{
		(*it)->update();
		(*it)->draw();
	}
}

LayerManager::LayerManager(sf::RenderWindow *gameWindow, TextureManager *TextureManager)
{
	_gameWindow = gameWindow;
	_textureManager = TextureManager;
}
