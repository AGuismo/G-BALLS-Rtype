//
// Sprite.hh for spritemanager in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:22:09 2013 brigno
// Last update Thu Nov 21 14:48:43 2013 lambert kevin
//

#ifndef TEXTURE_MANAGER_H_
# define TEXTURE_MANAGER_H_

# include	<exception>
# include	<map>
# include	<string>

class	Texture;

class	TextureManager
{
  typedef std::map<std::string, Texture *>	Texture_type;
private:
  TextureManager(void);
  virtual ~TextureManager(void);

public:
  static TextureManager	&getInstance(void);

public:
  void			addTexture(const std::string &name, const std::string &path);
  void			addTexture(const std::string &, Texture *);
  void			delTexture(const std::string &);
  Texture		*getTexture(const std::string &);

private:
  TextureManager(TextureManager const&);
  TextureManager& operator=(TextureManager const&);

private:
  Texture_type	_lnk;

public:
  class Exception
  {
  public:
    Exception(const std::string &msg) throw();
    virtual ~Exception() throw();

  public:
    Exception(Exception const&) throw();
    Exception& operator=(Exception const&) throw();

  public:
    virtual const char	*what() const throw();

  private:
    std::string		_what;
  };
};

#endif /* TEXTURE_MANAGER_H_ */
