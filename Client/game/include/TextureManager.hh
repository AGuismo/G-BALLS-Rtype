#ifndef TEXTUREMANAGER_
# define TEXTUREMANAGER_

#include	<iostream>
#include	<map>
#include	<SFML/Graphics.hpp>
#include	"Entity.hh"
#include	"Animation.hh"

namespace	game
{

  class		TextureManager
  {
  public:
    struct Key
    {
      Entity::type	type;
      std::string	action;
      int			frame;

      Key(const Entity::type &type, const std::string &action = Animation::ACT_DEFAULT, int frame = 0) :
	type(type), action(action), frame(frame) {}

      bool	operator<(const Key &rhs) const
      {
	if (type.full < rhs.type.full) return true;
	if (type.full > rhs.type.full) return false;
	if (action < rhs.action) return true;
	if (action > rhs.action) return false;
	if (frame < rhs.frame) return true;
	if (frame > rhs.frame) return false;
	return false;
      }
    };

  public:
    typedef std::map<std::string, sf::Image*> image_map_type;
    typedef std::map<Key, sf::Texture*> texture_map_type;

  public:
    const texture_map_type	getTextureByType(const Entity::type &type) const;
    const sf::Texture	*getTexture(const Key &key) const;
    const sf::Image		*getImage(const std::string &ImagePath) const;
    bool			addTexture(const std::string &ImagePath, const Key &key,
					   const sf::IntRect &rect = sf::IntRect());

    TextureManager() {};
    ~TextureManager();

  private:
    image_map_type		_images;
    texture_map_type		_textures;

  private:
    TextureManager(const TextureManager &);
    TextureManager			operator=(const TextureManager &);
  };
}

#endif // !TEXTUREMANAGER_
