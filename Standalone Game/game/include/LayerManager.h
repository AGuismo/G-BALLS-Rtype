#ifndef LAYERMANAGER_
# define	LAYERMANAGER_

#include	<deque>

# include	"EnumObject.h"
# include	"EnumLayer.h"
# include	"Layer.h"
# include	"RequestCode.hh"

class TextureManager;

namespace sf
{
  class RenderWindow;
}

namespace	game
{
  class		TextureManager;
}

class								LayerManager
{
 private:
  sf::RenderWindow				*_gameWindow;
  game::TextureManager				*_textureManager;

 private:
  typedef std::deque<Layer *>		 layers_type;
  layers_type						_layers;

 private:
  Layer							*findLayer(int lId);

 public:
  bool							addLayer(game::Type objType, LayerType lType, const sf::Vector2f &lInit,
								 const sf::Vector2f &lReset, const sf::Vector2f &lLim,
								 const sf::Vector2f &lInc, Timer *lTimer, bool lEn);
  bool							enableLayer(LayerType layer);
  bool							stopLayer(LayerType layer);

 public:
  void							draw(void);
  void							update(void);
  void							upDraw(void);

 public:
  LayerManager(sf::RenderWindow *gameWindow, game::TextureManager *TextureManager);
  ~LayerManager();

 private:
  LayerManager(const LayerManager &);
  LayerManager					operator=(const LayerManager &);
};


#endif // !LAYERMANAGER_
