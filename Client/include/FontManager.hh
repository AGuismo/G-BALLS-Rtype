//
// Sprite.hh for spritemanager in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 22:22:09 2013 brigno
// Last update Fri Nov 22 21:05:05 2013 brigno
//

#ifndef FONT_MANAGER_H_
# define FONT_MANAGER_H_

# include	<exception>
# include	<map>
# include	<string>

class	Font;

class	FontManager
{
  typedef std::map<std::string, Font *>	Font_type;
private:
  FontManager(void);
  virtual ~FontManager(void);

public:
  static FontManager	&getInstance(void);

public:
  void			addFont(const std::string &name, const std::string &path);
  void			addFont(const std::string &, Font *);
  void			delFont(const std::string &);
  Font			*getFont(const std::string &);

private:
  FontManager(FontManager const&);
  FontManager& operator=(FontManager const&);

private:
  Font_type	_lnk;

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

#endif /* FONT_MANAGER_H_ */
