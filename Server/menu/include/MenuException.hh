#ifndef MENU_EXCEPTION_H
# define MENU_EXCEPTION_H

# include	<string>
# include	<exception>

namespace	menu
{
  class		Exception : public std::exception
  {
  public:
    Exception(const std::string &) throw();
    Exception(Exception const&) throw();
    virtual ~Exception() throw();

  public:
    const char	*what() const throw();

  public:
    Exception& operator=(Exception const&) throw();

  protected:
    std::string	_what;
  };
}

#endif /* MENU_EXCEPTION_H */
