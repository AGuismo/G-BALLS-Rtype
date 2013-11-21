#ifndef TEXTUREMANAGER_
# define TEXTUREMANAGER_

#include	<iostream>
#include	<map>
#include	<SFML/Graphics.hpp>
#include	"EnumObject.h"


namespace	game
{
  class		TextureManager
  {
  public:
    typedef std::map<ObjType, sf::Texture*> map_type;

  private:
    map_type				 _spriteMap;

  public:
    sf::Texture				*getTexture(ObjType);
    bool					addTexture(ObjType, const std::string &texturePath);
    TextureManager() {}
    ~TextureManager() {}

  private:
    TextureManager(const TextureManager &);
    TextureManager			operator=(const TextureManager &);
  };
}

#endif // !TEXTUREMANAGER_
