#include	"SpriteManager.h"


sf::Texture				*SpriteManager::getTexture(ObjType obj)
{
	map_type::iterator	it = _spriteMap.find(obj);

	return (it == _spriteMap.end() ? NULL : it->second);
}

bool					SpriteManager::addTexture(ObjType obj, std::string &texturePath)
{
	sf::Texture			*newTexture = new sf::Texture;

	if (!newTexture->loadFromFile(texturePath.c_str()))
		return false;
	else
		_spriteMap[obj] = newTexture;
	return true;
}