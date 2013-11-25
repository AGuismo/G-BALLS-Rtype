#ifndef TEXTUREMANAGER_
# define TEXTUREMANAGER_

#include	<iostream>
#include	<map>
#include	<SFML/Graphics.hpp>
#include	"EnumObject.h"
#include	"RequestCode.hh"

namespace	game
{
  class		TextureManager
  {
  public:
    typedef std::map<game::Type, sf::Texture*> map_type;

  private:
    map_type				 _spriteMap;

  public:
    sf::Texture				*getTexture(game::Type);
    bool					addTexture(game::Type, const std::string &texturePath);
    TextureManager() {}
    ~TextureManager();

  private:
    TextureManager(const TextureManager &);
    TextureManager			operator=(const TextureManager &);
  };
}

#endif // !TEXTUREMANAGER_
