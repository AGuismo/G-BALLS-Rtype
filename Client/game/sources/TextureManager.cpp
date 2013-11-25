#include	"TextureManager.h"


namespace	game
{
  TextureManager::~TextureManager()
  {
    for (map_type::iterator it = _spriteMap.begin(); it != _spriteMap.end(); ++it)
      delete it->second;
    _spriteMap.clear();
  }

  sf::Texture				*TextureManager::getTexture(game::Type obj)
  {
    map_type::iterator	it = _spriteMap.find(obj);

    return (it == _spriteMap.end() ? NULL : it->second);
  }

  bool					TextureManager::addTexture(game::Type obj, const std::string &texturePath)
  {
    sf::Texture			*newTexture = new sf::Texture;

    if (!newTexture->loadFromFile(texturePath.c_str()))
      return false;
    else
      _spriteMap[obj] = newTexture;
    return true;
  }
}
