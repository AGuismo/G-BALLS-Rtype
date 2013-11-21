#include	"TextureManager.h"


sf::Texture				*TextureManager::getTexture(ObjType obj)
{
	map_type::iterator	it = _spriteMap.find(obj);

	return (it == _spriteMap.end() ? NULL : it->second);
}

bool					TextureManager::addTexture(ObjType obj, const std::string &texturePath)
{
	sf::Texture			*newTexture = new sf::Texture;

	if (!newTexture->loadFromFile(texturePath.c_str()))
		return false;
	else
		_spriteMap[obj] = newTexture;
	return true;
}
