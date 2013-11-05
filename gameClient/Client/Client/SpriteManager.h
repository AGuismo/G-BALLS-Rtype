#ifndef SPRITEMANAGER
# define SPRITEMANAGER

#include	<iostream>
#include	<map>
#include	<SFML/Graphics.hpp>
#include	"EnumObject.h"


class				SpriteManager
{
public:
	typedef std::map<ObjType, sf::Texture> map_type;
private:
	std::map<ObjType, sf::Texture> _spriteMap;

public:
	const sf::Texture		*getTexture(ObjType);
	bool					addTexture(ObjType, std::string &texturePath);
	SpriteManager() {}
	~SpriteManager() {}

private:
	SpriteManager(const SpriteManager &);
	SpriteManager			operator=(const SpriteManager &);
};


#endif // !SPRITEMANAGER