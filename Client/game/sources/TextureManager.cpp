#include	"TextureManager.hh"


namespace	game
{
  TextureManager::~TextureManager()
  {
    for (texture_map_type::iterator it = _textures.begin(); it != _textures.end(); ++it)
      delete it->second;
    for (image_map_type::iterator it = _images.begin(); it != _images.end(); ++it)
      delete it->second;
  }

  const sf::Texture	*TextureManager::getTexture(const Key &key) const
  {
    texture_map_type::const_iterator	it = _textures.find(key);

    if (it == _textures.end())
      return (NULL);
    return (it->second);
  }

  const sf::Image		*TextureManager::getImage(const std::string &ImagePath) const
  {
    image_map_type::const_iterator	it = _images.find(ImagePath);

    return (it != _images.end() ? it->second : NULL);
  }

  bool					TextureManager::addTexture(const std::string &ImagePath, const Key &key, const sf::IntRect &rect)
  {
    const sf::Image		*image = getImage(ImagePath);
    sf::Texture			*newTexture;

    if (_textures.find(key) != _textures.end())
      return (false);
    if (image == NULL)
    {
      sf::Image	*newImage = new sf::Image();

      if (!newImage->loadFromFile(ImagePath))
	return false;
      _images[ImagePath] = newImage;
      image = newImage;
    }
    newTexture = new sf::Texture();
    if (!newTexture->loadFromImage(*image, rect))
      return (false);
    _textures[key] = newTexture;
    return true;
  }

  const TextureManager::texture_map_type	TextureManager::getTextureByType(const Entity::type &type) const
  {
    texture_map_type	result;

    for (texture_map_type::const_iterator it = _textures.begin(); it != _textures.end(); ++it)
    {
      if (it->first.type.full == type.full)
	result.insert(*it);
    }
    return (result);
  }


}
